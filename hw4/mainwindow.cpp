/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 4
 * File: source file for MainWindow class that defines handlers for
 *       the four required actions in the spec, and helper functions
 */

#include "mainwindow.h"


//default constructor
MainWindow::MainWindow(QWidget *parent)
    : QSplitter(parent)
{
    adviceList = NULL;
    weatherList = NULL;
    reminderList = NULL;
}


//destructor
MainWindow::~MainWindow()
{
    delete adviceList;
    delete weatherList;
    delete reminderList;
}

//handler for giving advice
void MainWindow::adviceHandler()
{
    if(adviceList) {
        QString advice;
        if(!adviceList->empty()) {
            advice = this->getRandomString(adviceList);
        }
        else {
            advice = "";
        }
        emit this->appendText("Advice: " + advice);
    }
}

//handler for giving weather
void MainWindow::weatherHandler()
{
    if(weatherList) {
        QString weather;
        if(!weatherList->empty()) {
            weather = this->getRandomString(weatherList);
        }
        else {
            weather = "";
        }
        emit this->appendText("Weather: " + weather);
    }
}

//handler for giving reminders
void MainWindow::reminderHandler()
{
    if(reminderList) {
        if(!reminderList->empty()) {
            QString reminderText;
            int listIndex;
            reminderText = this->getRandomString(reminderList, listIndex);

            //create a random datetime object
            QDateTime randomDate(QDate((qrand() % 100) + 1950, (qrand() % 12) + 1,
                                       (qrand() % 28) + 1),
                                 QTime(qrand() % 24, qrand() % 60, 0));

            //append the date in the required format to the output text
            reminderText += " at " + randomDate.toString("h:mm A, dddd MM/dd/yyyy");

            //create a message box with a checkbox
            QMessageBox reminderBox;
            QCheckBox* showAgain = new QCheckBox;
            showAgain->setChecked(true);
            showAgain->setText("Show this message again");
            reminderBox.setIcon(QMessageBox::Information);
            reminderBox.setWindowTitle(tr("Advisor"));
            reminderBox.setText(reminderText);
            reminderBox.setCheckBox(showAgain);
            reminderBox.exec();
            //remove printed string from list if checkbox was unchecked
            if(!reminderBox.checkBox()->isChecked()) {
                reminderList->removeAt(listIndex);
            }
        }
        else {
            emit this->appendText("There are no more reminder messages");
        }
    }
}

//handler for quit action
void MainWindow::quitHandler()
{
    //create a yes/no dialog
    QMessageBox quitBox;
    quitBox.setWindowTitle("Advisor");
    quitBox.setText("Are you sure you want to quit?");
    quitBox.setIcon(QMessageBox::Question);
    quitBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    quitBox.setDefaultButton(QMessageBox::No);
    int ret = quitBox.exec();

    //send quit signal if user said yes
    switch (ret) {
        case QMessageBox::Yes :
            emit this->quitApp();
            break;
        case QMessageBox::No :
            break;
    }
}

//read in the files and store them to their corrosponding lists
void MainWindow::readFiles()
{
    try {
        adviceList = this->getFileArray("advice.dat");
    }
    catch(std::runtime_error e) {
        emit this->appendText(e.what());
    }
    try {
        weatherList = this->getFileArray("weather.dat");
    }
    catch(std::runtime_error e) {
        emit this->appendText(e.what());
    }
    try {
        reminderList = this->getFileArray("reminder.dat");
    }
    catch(std::runtime_error e) {
        emit this->appendText(e.what());
    }
}

//helper function for reading files and storing the lines in a QStringList
QStringList* MainWindow::getFileArray(const QString& fileName)
{
    QStringList* ret = new QStringList();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error("Error: no file with name " + fileName.toStdString() + " found");
    }

    while (!file.atEnd()) {
        QString line = file.readLine().trimmed(); //read line and remove newline character
        while(line.endsWith('\\')) {
            if(file.atEnd()) {
                //throw exception
                throw std::runtime_error("Backslash at end of last line of file " +
                                         fileName.toStdString());
            }
            else
            {
                line.chop(1); //chop off the backslash
                line += file.readLine().trimmed();
            }
        }
        ret->append(line);
    }
    return ret;
}

//helper function to get a random string from a string list
QString MainWindow::getRandomString(const QStringList* list)
{
    QString ret;
    ret = list->at(qrand() % list->length());
    return ret;
}

//overloaded random string getter that also allows an int to be passed in which specifies
//the randomly chosen index
QString MainWindow::getRandomString(const QStringList* list, int &rand)
{
    QString ret;
    rand = qrand() % list->length();
    ret = list->at(rand);
    return ret;
}
