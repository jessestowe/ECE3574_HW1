#ifndef BIRTHDAY_H
#define BIRTHDAY_H

#include <QDate>
#include <QString>

class Birthday
{
public:
    Birthday(QString name, QDate date);
    QString getName();
    QDate getDate();
    void setName(QString newName);
    void setDate(QDate newDate);
    bool operator==(const Birthday& b) const;
private:
    QString name;
    QDate date;
};

#endif // BIRTHDAY_H
