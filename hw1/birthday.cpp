/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 1
 * File: class definition of birthday
 */

#include "birthday.h"

//default constructor
Birthday::Birthday()
{

}

//creates a birthday with a name and date
Birthday::Birthday(QString newName, QDate newDate)
{
    name = newName;
    date = newDate;
}

//returns the name of the birthday
QString Birthday::getName() const
{
    return name;
}

//returns the date of the birthday
QDate Birthday::getDate() const
{
    return date;
}

//sets the name for the birthday
void Birthday::setName(QString newName)
{
    name = newName;
}

//sets the date for the birthday
void Birthday::setDate(QDate newDate)
{
    date = newDate;
}

//implements equality operation
bool Birthday::operator ==(const Birthday& b) const
{
    return (this->name == b.name) && (this->date == b.date);
}
