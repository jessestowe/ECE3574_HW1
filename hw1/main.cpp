/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 1
 * File: main file containing main function
*/

#include <QCoreApplication>
#include <QDate>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QList>
#include <exception>

#include "birthday.h"
#include "birthdaylist.h"

#define DATAFILE "birthdays.dat"    //file to store birthday data
#define DATEFORMAT Qt::ISODate      //date format for QDates


//define functions
void printBirthdays(QTextStream& out, QList<Birthday*> birthdayList);
bool isValidASCII(QString input);

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
       line = QString(dataFile.readLine()).split(" ");  //break the line up into sections
       QString takeFirst = line.takeFirst(); //first arg is date
       QDate date = QDate::fromString(takeFirst, DATEFORMAT);
       QString name;
       //take all subsequent sections and turn into name
       for(int i = 0; i < line.size(); ++i) {
           name += line[i] + " ";
       }
       name.chop(2); //remove last space and newline char
       birthdays.addBirthday(Birthday(name, date)); //add the birthday
    }
    //close the file after reading all of the data
    dataFile.close();

    //check for and handle command line args
    try {
        if(argc > 1) {
            if(strcmp(argv[1], "-a") == 0) {           //add birthday specified
                QString name = QString(argv[3]);

                //check to see if valid ASCII
                if(!isValidASCII(name)) {
                    throw std::invalid_argument("Invalid name");
                }
                QDate newDate = QDate::fromString(argv[2], DATEFORMAT);

                //check for valid date
                if(newDate < QDate::currentDate() || !newDate.isValid()) {
                    throw std::invalid_argument("Invalid date");
                }

                //if valid, add the birthday to birthdaylist
                birthdays.addBirthday(
                    Birthday(QString(argv[3]), newDate)
                );
            }
            else if(strcmp(argv[1], "-n") == 0) {      //list birthdays coming up in n days
                //find and print birthdays in range of current date for argv[2] number of days
                printBirthdays(qtCout, birthdays.findInRange(QDate::currentDate(), atoi(argv[2])));
            }
            else if(strcmp(argv[1], "-d") == 0) {      //delete birthdays
                if(argv[2][0] > 48 && argv[2][0] < 57) { // if the arg starts with a decimal number
                    //then delete based on date
                    QDate newDate = QDate::fromString(argv[2], DATEFORMAT);

                    //check for invalid date
                    if(newDate < QDate::currentDate() || !newDate.isValid()) {
                        throw std::invalid_argument("Invalid date");
                    }
                    //find and delete all birthdays on given date
                    QList<Birthday*> toDelete = birthdays.findInRange(newDate, 0);
                    for(int i = 0; i < toDelete.size(); ++ i) {
                        birthdays.removeBirthday(*toDelete[i]);
                    }
                }
                else {
                    //delete by name case
                    Birthday* toRemove = &(*birthdays.findByName(QString(argv[2])));

                    //check to see if no birthday with given name was found
                    if(toRemove == nullptr) {
                        throw std::invalid_argument("No birthdays found");
                    }
                    //if found, remove
                    birthdays.removeBirthday(*toRemove);
                }

            }
            else if(strcmp(argv[1], "-m") == 0) {      //birthdays after specified birthday and date range
                Birthday* startBirthday = birthdays.findByName(argv[2]);

                //check to see if no name found
                if(startBirthday == nullptr) {
                    throw std::range_error("Name not found");
                }
                QDate date = startBirthday->getDate();
                //print out birthdays in range
                printBirthdays(qtCout, birthdays.findInRange(date, atoi(argv[3])));
            }
            else if(strcmp(argv[1], "-u") == 0) {      //update case
                birthdays.refreshBirthdays();
            }
            else {                                      //namespec case
                //check for valid ASCII
                QString namespec = QString(argv[1]);
                if(!isValidASCII(namespec)) {
                    throw std::invalid_argument("Invalid name");
                }
                else {
                    //if valid, print out birthdays matching namespec
                    printBirthdays(qtCout, birthdays.searchNames(namespec));
                }
            }
        }
        else {                                          //no command line args given, print default behaviour
            //print out all birthdays in next 30 days
            printBirthdays(qtCout, birthdays.findInRange(QDate::currentDate(), 30));

        }
    }
    //catch all exceptions and print their error message to stderr
    catch (const std::exception& e)
    {
        qtCerr << e.what() << endl;
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
    //close the file
    dataFile.close();

    //return a.exec();
    return EXIT_SUCCESS;

}

/* Takes a textstream and list of birthdays and prints them to the stream
 * Inputs: QTextStream out - stream to print to
 *         QList<Birthday*> birthdayList - list of birthdays to print
 * Outputs: None
 */
void printBirthdays(QTextStream& out, QList<Birthday*> birthdayList)
{
    //check if no birthdays to print
    if(birthdayList.size() != 0) {
        out << "Name\t\t\tBirthday\n" << "=========\t\t============\n";
        for(int i = 0; i < birthdayList.size(); ++i) {
            out << birthdayList[i]->getName() << "\t\t" << birthdayList[i]->getDate().toString(DATEFORMAT) << "\n";
        }
    }
    else {
        out << "No birthdays found\n";
    }
}

/* check if the input QString is valid ASCII (any printable char besides newline and tabs)
 * Inputs: QString input - string to check
 * Outputs: None
 */
bool isValidASCII(QString input)
{
    bool ret = true;
    for(int i = 0; i < input.size(); ++i) {
        if(input[i] < 32 || input[i] > 126) {
            ret = false;
            break;
        }
    }
    return ret;
}


