#include <QCoreApplication>
#include <QDate>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QList>
#include "birthday.h"

#define DATAFILE "birthdays.dat"

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
    while(!dataFile.atEnd()) {
        QStringList split
        dataFile.readLine();
        input.split(" ");

        birthdays.addBirthday();
    }

    // print out all birthdays
//    for (int i = 0; i < birthdays.size(); ++i) {
//        qtCout << birthdays.at(i).toLocal8Bit().constData() << endl;
//    }

    dataFile.close();

    //return a.exec();
    return EXIT_SUCCESS;

}


