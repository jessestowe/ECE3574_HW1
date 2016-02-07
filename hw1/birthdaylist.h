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
