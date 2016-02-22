/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: header file for educational derived class of film
 */

#ifndef EDUCATIONAL_H
#define EDUCATIONAL_H

#include "film.h"

typedef quint32 Grade; //grade is just a quint32

class Educational: public Film
{
public:
    Educational(QString id, QString title, QString dir, quint32 len,
                QDate relDate, QString subject, Grade grade);
    Educational(QStringList& propList);
    QString toString(bool labeled, QString sepchar) const;
    QString getSubject();
    Grade getGradeLevel();
private:
    QString m_Subject;
    Grade m_GradeLevel;
};

#endif // EDUCATIONAL_H
