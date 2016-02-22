/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: class definition file for Educational derived class of Film
 */

#include "educational.h"

//constructor for educational class with params
Educational::Educational(QString id, QString title, QString dir, quint32 len, QDate relDate, QString subject, Grade grade) : Film(id, title, dir, len, relDate),
    m_Subject(subject), m_GradeLevel(grade)
{

}
//constructor for educational class with a StringList as param
Educational::Educational(QStringList& propList) : Film(propList),
    m_Subject(propList.takeFirst())
{
    bool isValidGrade;
    m_GradeLevel = propList.takeFirst().toUInt(&isValidGrade);
    if(!isValidGrade) {
        throw std::invalid_argument("invalid Grade");
    }
}

//returns a QString with all of the information from the film with sepchar and labels if specified
QString Educational::toString(bool labeled, QString sepchar) const
{
    if(labeled) {
        return QString("%1%2%3%4%5%6%7").arg(Film::toString(labeled, sepchar)).arg(sepchar)
                .arg("Subject: ").arg(m_Subject).arg(sepchar).arg("Grade: ").arg(m_GradeLevel);
    }
    else {
        return QString("%1%2%3%4%5").arg(Film::toString(labeled, sepchar))
                .arg(sepchar).arg(m_Subject).arg(sepchar).arg(m_GradeLevel);
    }
}

//getter for subject
QString Educational::getSubject()
{
    return m_Subject;
}

//getter for grade level
Grade Educational::getGradeLevel()
{
    return m_GradeLevel;
}
