#include "birthdaylist.h"

BirthdayList::BirthdayList()
{

}

void BirthdayList::addBirthday(Birthday newBDay)
{
    birthdays.append(newBDay);
}

void BirthdayList::removeBirthday(Birthday bDay)
{
    birthdays.removeOne(bDay);
}

QList<Birthday*> BirthdayList::findInRange(QDate startDate, int numDays)
{
    QList<Birthday*> ret;
    for(int i = 0; i < birthdays.size(); ++i) {
        if(birthdays[i].getDate() >= startDate &&
                birthdays[i].getDate() <= startDate.addDays(numDays)) {
            ret.append(&birthdays[i]);
        }
    }
    return ret;
}

QList<Birthday*> BirthdayList::searchNames(QString subString)
{
    QList<Birthday*> ret;
    for(int i = 0; i < birthdays.size(); ++i) {
        if(birthdays[i].getName().indexOf(subString) >= 0) {
            ret.append(&birthdays[i]);
        }
    }
    return ret;
}

Birthday* BirthdayList::findByName(QString name)
{
    for(int i = 0; i < birthdays.size(); ++i) {
        if(birthdays[i].getName() == name) {
            return &birthdays[i];
        }
    }
    return NULL;
}
