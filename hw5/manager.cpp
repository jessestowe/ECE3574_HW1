#include "manager.h"

Manager::Manager(const int instId, const char* boxName, const float temperature, mqd_t mailbox,
                 QList<const char*> upIds, QList<const char*> downIds) :
    m_IsOpen(false), m_Exit(false), m_InstId(instId), m_BoxName(boxName), m_ChildReceived(false),
    m_Temperature(temperature), m_Mailbox(mailbox), m_UpIds(upIds), m_DownIds(downIds)
{

}

void Manager::start()
{
    this->openMailboxes();
    this->sendDown(m_InstId);
}

void Manager::receiveTemp()
{
    char buf[sizeof(float)+1];
    unsigned int * sendingNode = new unsigned int(0);
    int msgLength;

    std::cout << "Process #" << m_InstId << ": initial temperature "
              << m_Temperature << std::endl;

    while(1) {
        if(m_Exit) {
            break;
        }
        msgLength = mq_receive(m_Mailbox, buf, sizeof(float)+1, sendingNode);
        if(msgLength >= 0) {
            float tempReceived = unpackFloat(buf);
            if(!m_IsOpen) {
                this->openMailboxes();
            }
            processMessage(tempReceived, *sendingNode);

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
            mqd_t tempBox = mq_open(m_UpIds[i], O_WRONLY);
            if(tempBox == (mqd_t) -1) {
                std::cout << "Error opening mailbox " << m_UpIds[i] << " from node " << m_InstId
                          << " with error " << strerror(errno) << std::endl;
                this->exit(EXIT_FAILURE);
            }
            m_UpMQ.append(tempBox);
        }
        for(int i = 0; i < m_DownIds.size(); i++) {
            mqd_t tempBox = mq_open(m_DownIds[i], O_WRONLY);
            if(tempBox == (mqd_t) -1) {
                std::cout << "Error opening mailbox " << m_DownIds[i] << " from node " << m_InstId
                          << " with error " << strerror(errno) << std::endl;
                this->exit(EXIT_FAILURE);
            }
            m_DownMQ.append(tempBox);
        }
        m_IsOpen = true;
    }
}

void Manager::sendDown(int sendingNode)
{
    char buf[sizeof(float)+1];
    this->packFloat(buf, m_Temperature);
    for(int i = 0; i < m_DownMQ.size(); i++) {
        if(mq_send(m_DownMQ[i], buf, sizeof(float)+1, sendingNode)) {
            std::cout << "Error sending message " << m_Temperature << " from node "
                      << m_InstId << " to node " << m_DownIds[i] << " with error: " << strerror(errno) << std::endl;
        }
    }
}

void Manager::sendUp(int sendingNode)
{
    std::cout << "Process #" << m_InstId << ": current temperature "
              << m_Temperature << std::endl;
    char buf[sizeof(float)];
    this->packFloat(buf, m_Temperature);
    for(int i = 0; i < m_UpMQ.size(); i++) {
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
                    if(fabs(tempTemperature - m_Temperature) < 0.01) {
                        m_Temperature = tempTemperature;
                        this->sendDown(8);
                        std::cout << "Process #" << m_InstId << ": final temperature "
                                  << m_Temperature << std::endl;
                        this->exit(EXIT_SUCCESS);
                    }
                    else {
                        m_Temperature = tempTemperature;
                        std::cout << "Process #" << m_InstId << ": current temperature "
                                  << m_Temperature << std::endl;
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

float Manager::unpackFloat(const void *buf) {
    const unsigned char *b = (const unsigned char *)buf;
    uint32_t temp = 0;
    temp = ((b[3] << 24) |
            (b[2] << 16) |
            (b[1] <<  8) |
             b[0]);
    return *((float *) &temp);
}

void Manager::packFloat(void * buf, float x) {
    unsigned char *f = (unsigned char *)&x;
    unsigned char *b = (unsigned char *)buf;
    b[0] = f[0];
    b[1] = f[1];
    b[2] = f[2];
    b[3] = f[3];
}

void Manager::exit(int exitCode)
{
    mq_close(m_Mailbox);
    mq_unlink(m_BoxName);
    std::exit(exitCode);
}
