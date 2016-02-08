/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 1
 * File: class definition of birthdaylist
 */

#include "birthdaylist.h"

//default constructor
BirthdayList::BirthdayList()
{

}


//adds a birthday to the list, updating birthday if same name is present
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

//removes a birthday from the list
void BirthdayList::removeBirthday(Birthday bDay)
{
    m_birthdays.removeOne(bDay);
}

//returns the number of birthdays in the list
int BirthdayList::size()
{
    return m_birthdays.size();
}

//returns a list of birthdays in range from a given start date for numDays number of days
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

//searchs the list for all birthdays whose name's contain subString
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

//returns the birthday with the given name
//if no match, returns nullptr
Birthday* BirthdayList::findByName(QString name)
{
    for(int i = 0; i < m_birthdays.size(); ++i) {
        if(m_birthdays[i].getName() == name) {
            return &m_birthdays[i];
        }
    }
    return nullptr;
}

//updates all birthdays so that they occur in the next year
//except feb 29, which updates to be in the next 4 years
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

//allows index style element access
Birthday& BirthdayList::operator[] (const int nIndex)
{
    return m_birthdays[nIndex];
}
