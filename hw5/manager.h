/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 5
 * File: header file for Manager class that handles message sending
 *       and receiving for each node
 */

#ifndef MANAGER_H
#define MANAGER_H

#include <QString>
#include <QList>
#include <iostream>
#include <pthread.h>
#include <mqueue.h>
#include <sstream>

class Manager
{
public:
    Manager(const int instId, const char* boxName, const float temperature, mqd_t mailbox,
            QList<const char*> upIds, QList<const char*> downIds);
    void start();
    void receiveTemp();
    void exit(int exitCode);
private:
    void openMailboxes();
    void sendDown(int sendingNode);
    void sendUp(int sendingNode);
    bool m_IsOpen;    // tracks if mailboxes are currently open
    bool m_Exit;
    unsigned int m_InstId;
    const char * m_BoxName;
    float m_ChildTemp;  // variable to store a child's temperature
    bool m_ChildReceived;
    float m_Temperature;
    mqd_t m_Mailbox;
    QList<const char*> m_UpIds;
    QList<const char*> m_DownIds;
    QList<mqd_t> m_UpMQ;
    QList<mqd_t> m_DownMQ;

    float unpackFloat(const void *buf);
    void packFloat(void * buf, float x);

    void processMessage(float message, unsigned int sendingNode);

};

#endif // MANAGER_H
