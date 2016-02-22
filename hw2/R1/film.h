/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: header file for film class which defines a film
 */

#ifndef FILM_H
#define FILM_H

#include <QDate>
#include <QString>
#include <QStringList>

class Film
{
public:
    virtual ~Film();
    QString virtual toString(bool labeled, QString sepchar) const;
    QString getID();
    QString getTitle();
    QString getDirector();
    quint32 getFilmLength();
    QDate getReleaseDate();
    Film(QString id, QString title, QString dir, quint32 length, QDate relDate);
    Film(QStringList& propList);

private:
    QString m_FilmID;
    QString m_Title;
    QString m_Director;
    quint32 m_FilmLength;
    QDate m_ReleaseDate;
};

#endif // FILM_H
