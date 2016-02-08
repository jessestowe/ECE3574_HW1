#include "birthdaylist.h"

BirthdayList::BirthdayList()
{

}

void BirthdayList::addBirthday(Birthday newBDay)
{
    Birthday* temp;
    temp = this->findByName(newBDay.getName());
    if(temp == nullptr) {
        m_birthdays.append(newBDay);
    }
    else {
        temp->setDate(newBDay.getDate());
    }
}

void BirthdayList::removeBirthday(Birthday bDay)
{
    m_birthdays.removeOne(bDay);
}

int BirthdayList::size()
{
    return m_birthdays.size();
}

QList<Birthday*> BirthdayList::findInRange(QDate startDate, int numDays)
{
    QList<Birthday*> ret;
    for(int i = 0; i < m_birthdays.size(); ++i) {
        if(m_birthdays[i].getDate() >= startDate &&
                m_birthdays[i].getDate() <= startDate.addDays(numDays)) {
            ret.append(&m_birthdays[i]);
        }
    }
    return ret;
}

QList<Birthday*> BirthdayList::searchNames(QString subString)
{
    QList<Birthday*> ret;
    for(int i = 0; i < m_birthdays.size(); ++i) {
        if(m_birthdays[i].getName().indexOf(subString) >= 0) {
            ret.append(&m_birthdays[i]);
        }
    }
    return ret;
}

Birthday* BirthdayList::findByName(QString name)
{
    for(int i = 0; i < m_birthdays.size(); ++i) {
        if(m_birthdays[i].getName() == name) {
            return &m_birthdays[i];
        }
    }
    return nullptr;
}

void BirthdayList::refreshBirthdays()
{
    QDate current = QDate::currentDate();
    for(int i = 0; i < m_birthdays.size(); ++i) {
        QDate oldBirthday = m_birthdays[i].getDate();
        if(oldBirthday.dayOfYear() > current.dayOfYear()) {
            m_birthdays[i].setDate(QDate(current.year(), oldBirthday.month(), oldBirthday.day()));
        }
        else {
            m_birthdays[i].setDate(QDate(current.year() + 1, oldBirthday.month(), oldBirthday.day()));
        }
        while(!m_birthdays[i].getDate().isValid()) {
            m_birthdays[i].setDate(QDate(m_birthdays[i].getDate().year() + 1, m_birthdays[i].getDate().month(), m_birthdays[i].getDate().day()));
        }
    }
}

Birthday& BirthdayList::operator[] (const int nIndex)
{
    return m_birthdays[nIndex];
}
