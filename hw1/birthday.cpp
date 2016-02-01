#include "birthday.h"

Birthday::Birthday(QString newName, QDate newDate)
{
    name = newName;
    date = newDate;
}

QString Birthday::getName() const
{
    return name;
}

QDate Birthday::getDate() const
{
    return date;
}

void Birthday::setName(QString newName)
{
    name = newName;
}

void Birthday::setDate(QDate newDate)
{
    date = newDate;
}

bool Birthday::operator ==(const Birthday& b) const
{
    return this->name == b.getName() && this->date == b.getDate();
}
