/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 4
 * File: header file for MainWindow class
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSplitter>
#include <QMainWindow>
#include <QFile>
#include <QStringList>
#include <QMessageBox>
#include <QDateTime>
#include <QCheckBox>

class MainWindow : public QSplitter
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //reads in the required files, and emits an appendText signal on error
    //must be called before handlers
    void readFiles();

public slots:
    //handlers for required actions
    void adviceHandler();
    void weatherHandler();
    void reminderHandler();
    void quitHandler();

signals:
    //output from the handlers is emitted in the appendText signal
    void appendText(QString newText);
    //when the "yes" button is pressed in the quit dialog, this signal is emitted
    void quitApp();

private:
    //helper functions for handlers
    QStringList* getFileArray(const QString& fileName);
    QString getRandomString(const QStringList *list);
    QString getRandomString(const QStringList* list, int &rand);

    //variables to store strings read from files
    QStringList* adviceList;
    QStringList* weatherList;
    QStringList* reminderList;
};

#endif // MAINWINDOW_H
