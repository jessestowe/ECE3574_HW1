#ifndef MANAGER_H
#define MANAGER_H

#include <QString>
#include <QList>
#include <iostream>
#include <pthread.h>
#include <mqueue.h>

class Manager
{
public:
    Manager(const int instId, const float temperature, mqd_t mailbox,
            QList<const char*> upIds, QList<const char*> downIds);
    void start();
    void receiveTemp();
private:
    void openMailboxes();
    void sendTemp();
    bool m_IsOpen;    // tracks if mailboxes are currently open
    int m_InstId;
    float m_Temperature;
    mqd_t m_Mailbox;
    QList<const char*> m_UpIds;
    QList<const char*> m_DownIds;
    QList<mqd_t> m_UpMQ;
    QList<mqd_t> m_DownMQ;

};

#endif // MANAGER_H
