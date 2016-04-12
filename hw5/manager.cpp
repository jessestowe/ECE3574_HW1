#include "manager.h"

Manager::Manager(const int instId, const char* boxName, const float temperature, mqd_t mailbox,
                 QList<const char*> upIds, QList<const char*> downIds) :
    m_IsOpen(false), m_Exit(false), m_InstId(instId), m_BoxName(boxName), m_ChildReceived(false),
    m_Temperature(temperature), m_Mailbox(mailbox), m_UpIds(upIds), m_DownIds(downIds)
{

}

void Manager::start()
{
    std::cout << "opening mailboxes" << std::endl;
    this->openMailboxes();
    std::cout << "sending down" << std::endl;
    this->sendDown(m_InstId);
    std::cout << "receiveTemp" << std::endl;
}

void Manager::receiveTemp()
{
    char buf[sizeof(float)];
    unsigned int * sendingNode = 0;
    int msgLength;

    while(1) {
        if(m_Exit) {
            break;
        }
        msgLength = mq_receive(m_Mailbox, buf, sizeof(float)+1, sendingNode);
        if(msgLength >= 0) {
            processMessage(unpackFloat(buf), *sendingNode);

        }
        else if(errno != EAGAIN){
            std::cout << "Error: " << strerror(errno) << std::endl;
            this->exit(EXIT_FAILURE);
        }
    }
}

void Manager::openMailboxes()
{
    if(!m_IsOpen) {
        for(int i = 0; i < m_UpIds.size(); i++) {
            mqd_t tempBox = mq_open(m_UpIds[i], 0);
            if(tempBox == (mqd_t)-1) {
                std::cout << "Error opening mailbox " << m_UpIds[i] << " from node " << m_InstId
                          << " with error " << strerror(errno) << std::endl;
                this->exit(EXIT_FAILURE);
            }
            m_UpMQ.append(tempBox);
        }
        for(int i = 0; i < m_DownIds.size(); i++) {
            mqd_t tempBox = mq_open(m_DownIds[i], 0);
            if(tempBox == (mqd_t)-1) {
                std::cout << "Error opening mailbox " << m_DownIds[i] << " from node " << m_InstId
                          << " with error " << strerror(errno) << std::endl;
                this->exit(EXIT_FAILURE);
            }
            m_DownMQ.append(tempBox);
        }
    }
}

void Manager::sendDown(int sendingNode)
{
    char buf[sizeof(float)];
    std::cout << buf << std::endl;
    this->packFloat(&buf[0], m_Temperature);
    std::cout << "message:" << buf[0] << std::endl;
    for(int i = 0; i < m_DownIds.size(); i++) {
        if(mq_send(m_DownMQ[i], buf, sizeof(float)+1, sendingNode)) {
            std::cout << "Error sending message " << m_Temperature << " from node "
                      << m_InstId << " to node " << m_DownIds[i] << std::endl;
        }
    }
}

void Manager::sendUp(int sendingNode)
{
    std::cout << "Process #" << m_InstId << ": current temperature "
              << m_Temperature << std::endl;
    char buf[sizeof(float)];
    this->packFloat(&buf[0], m_Temperature);
    for(int i = 0; i < m_UpIds.size(); i++) {
        if(mq_send(m_UpMQ[i], buf, sizeof(float), sendingNode)) {
            std::cout << "Error sending message " << m_Temperature << " from node "
                      << m_InstId << " to node " << m_UpIds[i] << std::endl;
        }
    }
}

void Manager::processMessage(float message, unsigned int sendingNode)
{
    // a "priority" of 8 is a special code to exit the program
    if(sendingNode == 8) {
        sendDown(8);
        std::cout << "Process #" << m_InstId << ": final temperature "
                  << m_Temperature << std::endl;
        this->exit(EXIT_SUCCESS);
    }
    // if a message has been received by a child
    else {
        if(sendingNode > m_InstId) {
            if(!m_ChildReceived) {
                m_ChildTemp = message;
                m_ChildReceived = true;
            }
            else {
                m_ChildReceived = false;
                float tempTemperature = (m_Temperature + message + m_ChildTemp)/3.0;
                if(m_InstId > 0) {
                    m_Temperature = tempTemperature;
                    this->sendUp(m_InstId);
                }
                else {
                    if(abs(tempTemperature - m_Temperature) < 0.01) {
                        this->sendDown(8);
                        std::cout << "Process #" << m_InstId << ": final temperature "
                                  << m_Temperature << std::endl;
                        this->exit(EXIT_SUCCESS);
                    }
                    else {
                        m_Temperature = tempTemperature;
                        this->sendDown(m_InstId);
                    }
                }
            }
        }
        // if a message has been received by a parent
        else if(sendingNode < m_InstId) {
            m_Temperature = (m_Temperature + message)/2.0;
            if(m_InstId > 2) {
                this->sendUp(m_InstId);
            }
            else {
                this->sendDown(m_InstId);
            }
        }
    }
}

// unpack method for retrieving data in network byte,
//   big endian, order (MSB first)
// increments index i by the number of bytes unpacked
// usage:
//   int i = 0;
//   float x = unpackFloat(&buffer[i], &i);
//   float y = unpackFloat(&buffer[i], &i);
//   float z = unpackFloat(&buffer[i], &i);
float Manager::unpackFloat(const void *buf) {
    const unsigned char *b = (const unsigned char *)buf;
    uint32_t temp = 0;
    temp = ((b[0] << 24) |
            (b[1] << 16) |
            (b[2] <<  8) |
             b[3]);
    return *((float *) temp);
}

// pack method for storing data in network,
//   big endian, byte order (MSB first)
// returns number of bytes packed
// usage:
//   float x, y, z;
//   int i = 0;
//   i += packFloat(&buffer[i], x);
//   i += packFloat(&buffer[i], y);
//   i += packFloat(&buffer[i], z);
int Manager::packFloat(void *buf, float x) {
    unsigned char *b = (unsigned char *)buf;
    unsigned char *p = (unsigned char *) &x;
#if defined (_M_IX86) || (defined (CPU_FAMILY) && (CPU_FAMILY == I80X86))
    b[0] = p[3];
    b[1] = p[2];
    b[2] = p[1];
    b[3] = p[0];
#else
    b[0] = p[0];
    b[1] = p[1];
    b[2] = p[2];
    b[3] = p[3];
#endif
    return 4;
}

void Manager::exit(int exitCode)
{
    mq_close(m_Mailbox);
    mq_unlink(m_BoxName);
    exit(exitCode);
}
