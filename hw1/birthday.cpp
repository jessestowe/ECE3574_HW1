#include "birthday.h"

Birthday::Birthday(QString name, QDate date)
{
    this->name = name;
    this->date = date;
}

QString Birthday::getName()
{
    return this->name;
}

QDate Birthday::getDate()
{
    return this->date;
}

void setName(QString newName)
{
    this->name = newName;
}

void setDate(QString newDate)
{
    this->date = newDate;
}

bool Birthday::operator ==(const Birthday& b) const
{
    return this->name == b->name && this->date == b->date;
}
