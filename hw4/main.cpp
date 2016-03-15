/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 4
 * File: main file that sets up the main window with 4 buttons and a text edit
 */

#include "mainwindow.h"
#include <QApplication>
#include <QTextEdit>
#include <QSplitter>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //create window
    MainWindow vsplitter;

    //setup a verital orientation
    vsplitter.setOrientation(Qt::Vertical);

    //create widgets
    QTextEdit textEdit;
    QPushButton buttonAdvice("Advice");
    QPushButton buttonWeather("Weather");
    QPushButton buttonReminder("Reminder");
    QPushButton buttonQuit("Quit");

    //add widgets to window
    vsplitter.addWidget(&textEdit);
    vsplitter.addWidget(&buttonAdvice);
    vsplitter.addWidget(&buttonWeather);
    vsplitter.addWidget(&buttonReminder);
    vsplitter.addWidget(&buttonQuit);
    vsplitter.setWindowTitle("Advisor");

    //connect buttons to their handlers
    QObject::connect(&buttonAdvice, &QPushButton::clicked, &vsplitter, &MainWindow::adviceHandler);
    QObject::connect(&buttonWeather, &QPushButton::clicked, &vsplitter, &MainWindow::weatherHandler);
    QObject::connect(&buttonReminder, &QPushButton::clicked, &vsplitter, &MainWindow::reminderHandler);
    QObject::connect(&buttonQuit, &QPushButton::clicked, &vsplitter, &MainWindow::quitHandler);

    QObject::connect(&vsplitter, &MainWindow::appendText, &textEdit, &QTextEdit::append);

    QObject::connect(&vsplitter, &MainWindow::quitApp, &a, &QApplication::quit);

    vsplitter.show();

    //read the files last so that error messages can be printed to the textedit window
    vsplitter.readFiles();

    return a.exec();
}
