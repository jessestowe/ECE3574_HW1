#ifndef BIRTHDAY_H
#define BIRTHDAY_H

#include <QDate>
#include <QString>

class Birthday
{
public:
    Birthday(QString newName, QDate newDate);
    QString getName() const;
    QDate getDate() const;
    void setName(QString newName);
    void setDate(QDate newDate);
    bool operator==(const Birthday& b) const;
private:
    QString name;
    QDate date;
};

#endif // BIRTHDAY_H
