/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 1
 * File: header file for birthdaylist
 */

#ifndef BIRTHDAYLIST_H
#define BIRTHDAYLIST_H

#include <QtCore/QList>
#include <QtCore/QDate>
#include <QtCore/QString>
#include <QtCore/QFile>
#include "birthday.h"

class BirthdayList
{
public:
    BirthdayList();
    void addBirthday(Birthday newBDay);
    void removeBirthday(Birthday bDay);
    int size();
    QList<Birthday*> findInRange(QDate startDate, int numDays);
    QList<Birthday*> searchNames(QString subString);
    Birthday* findByName(QString name);
    void refreshBirthdays();

    Birthday& operator[] (const int nIndex);
private:
    QList<Birthday> m_birthdays;

};

#endif // BIRTHDAYLIST_H
