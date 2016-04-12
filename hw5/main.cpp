#include <QList>
#include <pthread.h>
#include <mqueue.h>
#include <QString>
#include <iostream>

#include "manager.h"

int main(int argc, char *argv[])
{
    //check for proper number of args
    if(argc != 3) {
        std::cout << "Requires 2 arguments (" << argc - 1 << " given)" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    mqd_t mqMailbox;

    //setup message queue names
    const char* mqIds[] = {"/70", "/71", "/72", "/73", "/74", "/75", "/76"};

    // read and check the supplied instance ID
    QString arg(argv[1]);
    bool isValid;
    const int instId = arg.toInt(&isValid);
    if(!isValid || instId < 0 || instId > 6) {
        std::cout << "Invalid instance ID: " << arg.toStdString() << std::endl;
        exit(EXIT_FAILURE);
    }

    // read and check the supplied temperature
    arg = argv[2];
    const float temperature = arg.toFloat(&isValid);
    if(!isValid) {
        std::cout << "invalid temperature: " << arg.toStdString() << std::endl;
        exit(EXIT_FAILURE);
    }

    // setup message queue attributes
    struct mq_attr attr;
    attr.mq_flags = O_NONBLOCK;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 4;
    attr.mq_curmsgs = 0;

    // create message queue instance
    mqMailbox = mq_open(mqIds[instId], O_NONBLOCK | O_RDONLY | O_CREAT | O_EXCL, 0666, &attr);

    if(mqMailbox == (mqd_t)-1) {
        std::cout << "Error while creating message queue: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    QList<const char*> upIds, downIds;

    switch(instId) {
        case 0 : downIds.append(mqIds[1]);
                 downIds.append(mqIds[2]);
                 break;

        case 1 : downIds.append(mqIds[3]);
                 downIds.append(mqIds[4]);
                 upIds.append(mqIds[0]);
                 break;

        case 2 : downIds.append(mqIds[5]);
                 downIds.append(mqIds[6]);
                 upIds.append(mqIds[0]);
                 break;

        case 3 : upIds.append(mqIds[1]);
                 break;

        case 4 : upIds.append(mqIds[1]);
                 break;

        case 5 : upIds.append(mqIds[2]);
                 break;

        case 6 : upIds.append(mqIds[2]);
                 break;

        default : std::cout << "switch case failed" << std::endl;
                  break;
    }

    Manager messageManager(instId, mqIds[instId], temperature, mqMailbox, upIds, downIds);

    if(instId == 0) {
        messageManager.start();
    }
    messageManager.receiveTemp();

    mq_close(mqMailbox);
    mq_unlink(mqIds[instId]);

    return EXIT_SUCCESS;
}
