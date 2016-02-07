#include <QCoreApplication>
#include <QDate>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QList>
#include "birthday.h"
#include "birthdaylist.h"

#include <QDebug>

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
    dataFile.open(QIODevice::ReadOnly | QIODevice::Text);

    //read birthdays from file and save in string list
    BirthdayList birthdays;
    QStringList line;
    while (!dataFile.atEnd())
    {
       line = QString(dataFile.readLine()).split(" ");
       QString takeFirst = line.takeFirst();
       QDate date = QDate::fromString(takeFirst, DATEFORMAT);
       QString name;
       for(int i = 0; i < line.size(); ++i) {
           name += line[i] + " ";
       }
       name.chop(2); //remove last space and newline char
       birthdays.addBirthday(Birthday(name, date));
    }
    //close the file after reading all of the data
    dataFile.close();

    //check for and handle command line args
    if(argc > 1) {
        if(strcmp(argv[1], "-a") == 0) {           //add birthday specified
            birthdays.addBirthday(
                Birthday(QString(argv[3]), QDate::fromString(argv[2], DATEFORMAT))
            );
        }
        else if(strcmp(argv[1], "-n") == 0) {      //list birthdays coming up in n days
            printBirthdays(qtCout, birthdays.findInRange(QDate::currentDate(), atoi(argv[2])));
        }
        else if(strcmp(argv[1], "-d") == 0) {      //delete birthdays
            if(argv[2][0] > 48 && argv[2][0] < 57) { // if the arg starts with a decimal number
                QList<Birthday*> toDelete = birthdays.findInRange(QDate::fromString(argv[2], DATEFORMAT), 0);
                for(int i = 0; i < toDelete.size(); ++ i) {
                    birthdays.removeBirthday(*toDelete[i]);
                }
            }
            else {
                birthdays.removeBirthday(*birthdays.findByName(QString(argv[2])));
            }

        }
        else if(strcmp(argv[1], "-m") == 0) {      //birthdays after specified birthday and date range
            QDate date = birthdays.findByName(argv[2])->getDate();
            printBirthdays(qtCout, birthdays.findInRange(date, atoi(argv[3])));
        }
        else if(strcmp(argv[1], "-u") == 0) {      //update case
            birthdays.refreshBirthdays();
        }
        else {                                      //namespec case

        }
    }
    else {                                          //no command line args given, print default behaviour
        printBirthdays(qtCout, birthdays.findInRange(QDate::currentDate(), 30));

    }

    // write all birthdays back to file
    //open file for writing
    if(!dataFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qtCout << "EXIT FAILURE: could not open outfile for writing\n";
        return EXIT_FAILURE;
    }
    QTextStream fileOut(&dataFile);
    for(int i = 0; i < birthdays.size(); ++i) {
        fileOut << birthdays[i].getDate().toString(DATEFORMAT) << " " << birthdays[i].getName() << "\n";
    }


    dataFile.close();

    //return a.exec();
    return EXIT_SUCCESS;

}

void printBirthdays(QTextStream& out, QList<Birthday*> birthdayList)
{
    //print header
    out << "Name\t\t\tBirthday\n" << "=========\t\t============\n";
    for(int i = 0; i < birthdayList.size(); ++i) {
        out << birthdayList[i]->getName() << "\t\t" << birthdayList[i]->getDate().toString(DATEFORMAT) << "\n";
    }
}


