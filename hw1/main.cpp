#include <QCoreApplication>
#include <QDate>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QList>
#include "birthday.h"
#include "birthdaylist.h"

#define DATAFILE "birthdays.dat"
#define DATEFORMAT Qt::ISODate      //date format for QDates

void printBirthdays(QTextStream& out, QList<Birthday*> birthdayList);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Setup in/out streams
    QTextStream qtCout(stdout);
    QTextStream qtCerr(stderr);

    //Open birthday file
    QFile dataFile(DATAFILE);
    if(!dataFile.open(QIODevice::ReadWrite)){
        return EXIT_FAILURE;
    }

    //read birthdays from file and save in string list
    BirthdayList birthdays;
    QStringList line;
    while (!dataFile.atEnd())
    {
       line = QString(dataFile.readLine()).split(" ");
       birthdays.addBirthday(Birthday(line[0], QDate::fromString(line[1], DATEFORMAT)));
    }

    //check for and handle command line args
    if(argc > 1) {
        if(strcmp(argv[1], "-a") == 0) {           //add birthday specified
            birthdays.addBirthday(
                Birthday(QString(argv[3]).remove("\""), QDate::fromString(argv[2], DATEFORMAT))
            );
        }
        else if(strcmp(argv[1], "-n") == 0) {      //list birthdays coming up in n days
            printBirthdays(qtCout, birthdays.findInRange(QDate::currentDate(), atoi(argv[2])));
        }
        else if(strcmp(argv[1], "-d") == 0) {      //delete birthdays

        }
        else if(strcmp(argv[1], "-m") == 0) {      //birthdays after specified birthday and date range

        }
        else if(strcmp(argv[1], "-u") == 0) {      //update case

        }
        else {                                      //namespec case

        }
    }
    else {                                          //no command line args given, print default behaviour

    }

    // print out all birthdays
//    for (int i = 0; i < birthdays.size(); ++i) {
//        qtCout << birthdays.at(i).toLocal8Bit().constData() << endl;
//    }

    dataFile.close();

    //return a.exec();
    return EXIT_SUCCESS;

}

void printBirthdays(QTextStream& out, QList<Birthday*> birthdayList)
{

}


