#ifndef BIRTHDAYLIST_H
#define BIRTHDAYLIST_H

#include <QList>
#include <QDate>
#include <QString>
#include <QFile>
#include "birthday.h"

class BirthdayList
{
public:
    BirthdayList();
    void addBirthday(Birthday newBDay);
    void removeBirthday(Birthday bDay);
    QList<Birthday*> findInRange(QDate startDate, int numDays);
    QList<Birthday*> searchNames(QString subString);
    Birthday* findByName(QString name);
    void refreshBirthdays();
    void readFromFile(QFile input);
    void dumpToFile(QFile output);
private:
    QList<Birthday> birthdays;

};

#endif // BIRTHDAYLIST_H
