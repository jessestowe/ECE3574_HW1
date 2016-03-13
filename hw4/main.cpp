#include "mainwindow.h"
#include <QApplication>
#include <QTextEdit>
#include <QSplitter>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow vsplitter;

    vsplitter.setOrientation(Qt::Vertical);

    QTextEdit textEdit;

    QPushButton buttonAdvice("Advice");
    QPushButton buttonWeather("Weather");
    QPushButton buttonReminder("Reminder");
    QPushButton buttonQuit("Quit");

    vsplitter.addWidget(&textEdit);
    vsplitter.addWidget(&buttonAdvice);
    vsplitter.addWidget(&buttonWeather);
    vsplitter.addWidget(&buttonReminder);
    vsplitter.addWidget(&buttonQuit);
    vsplitter.setWindowTitle("Advisor");

    QObject::connect(&buttonAdvice, &QPushButton::clicked, &vsplitter, &MainWindow::adviceHandler);
    QObject::connect(&buttonWeather, &QPushButton::clicked, &vsplitter, &MainWindow::weatherHandler);
    QObject::connect(&buttonReminder, &QPushButton::clicked, &vsplitter, &MainWindow::reminderHandler);
    QObject::connect(&buttonQuit, &QPushButton::clicked, &vsplitter, &MainWindow::quitHandler);

    QObject::connect(&vsplitter, &MainWindow::appendText, &textEdit, &QTextEdit::append);

    vsplitter.show();

    vsplitter.readFiles();

    return a.exec();
}
