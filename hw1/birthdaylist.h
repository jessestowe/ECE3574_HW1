#ifndef BIRTHDAYLIST_H
#define BIRTHDAYLIST_H

#include <QString>
#include <QDate>
#include <QList>
#include <QStringList>
#include <QTextStream>

class BirthdayList
{
public:
    BirthdayList();
    ~BirthdayList();
    void addBirthday(QString name, QDate date);
    QDate getBirthday(QString name);
    QString getBirthday(QDate date);
    void delBirthday(QString name);
    void delBirthday(QDate date);
    void update();
    void printBirthdays(QTextStream& output);

private:
    int findBirthday(QString name);
    QStringList birthdayNames;
    QList<QDate> birthdayDates;
};

#endif // BIRTHDAYLIST_H
