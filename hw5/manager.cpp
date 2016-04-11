#include "manager.h"

Manager::Manager(const int instId, const float temperature, mqd_t mailbox,
                 QList<const char*> upIds, QList<const char*> downIds) :
    m_InstId(instId), m_Temperature(temperature), m_Mailbox(mailbox), m_UpIds(upIds),
    m_DownIds(downIds)
{

}

void Manager::start()
{
    this->openMailboxes();
    for(int i = 0; i < m_DownIds.size(); i++) {
        QString message = QString("Process #" << m_InstId << ": current temperature " << m_Temperature);
        if(mq_send(m_DownMQ[i], message.toLatin1().data(), message.size(), 0)) {
            std::cout << "Error sending message " << message.toStdString() << " from node "
                      << m_InstId << " to node " << m_DownIds[i] << std::endl;
        }
    }

}

void Manager::receiveTemp()
{

}

void Manager::openMailboxes()
{
    if(!m_IsOpen) {
        for(int i = 0; i < m_UpIds.size(); i++) {
            mqd_t tempBox = mq_open(m_UpIds[0], 0);
            if(tempBox == (mqd_t)-1) {
                std::cout << "Error opening mailbox " << m_UpIds[0] << " from node " << m_InstId
                          << " with error " << strerror(errno) << std::endl;
                exit(EXIT_FAILURE);
            }
            m_UpMQ.append(tempBox);
        }
        for(int i = 0; i < m_DownIds.size(); i++) {
            mqd_t tempBox = mq_open(m_DownIds[0], 0);
            if(tempBox == (mqd_t)-1) {
                std::cout << "Error opening mailbox " << m_DownIds[0] << " from node " << m_InstId
                          << " with error " << strerror(errno) << std::endl;
                exit(EXIT_FAILURE);
            }
            m_DownMQ.append(tempBox);
        }
    }
}

void Manager::sendTemp()
{
    for(int i = 0; i < )
}
