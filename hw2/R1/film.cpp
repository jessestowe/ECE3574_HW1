/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: definition file for Film class
 */

#include "film.h"

//constructor using individual params
Film::Film(QString id, QString title, QString dir, quint32 length, QDate relDate) : m_FilmID(id),
    m_Title(title), m_Director(dir), m_FilmLength(length), m_ReleaseDate(relDate)
{

}

//constructor using QStringList
Film::Film(QStringList& propList) : m_FilmID(propList.takeFirst()), m_Title(propList.takeFirst()),
    m_Director(propList.takeFirst())
{
    bool isValidLength;
    m_FilmLength = propList.takeFirst().toUInt(&isValidLength);
    if(!isValidLength) {
        throw std::invalid_argument("invalid length");
    }
    m_ReleaseDate = QDate::fromString(propList.takeFirst(), Qt::ISODate);
    if(!m_ReleaseDate.isValid()) {
        throw std::invalid_argument("invalid date");
    }
}

//virutal destructor doesn't need to do anything
Film::~Film()
{

}

//returns a QString with all of the information from the film
QString Film::toString(bool labeled, QString sepchar) const
{
    if(labeled) {
        return QString("%1%2%3%4%5%6%7%8%9%10%11%12%13%14").arg("ID: ").arg(m_FilmID).arg(sepchar).arg("Title: ")
                .arg(m_Title).arg(sepchar).arg("Director: ").arg(m_Director).arg(sepchar)
                .arg("Length: ").arg(m_FilmLength).arg(sepchar).arg("Release Date: ")
                .arg(m_ReleaseDate.toString(Qt::ISODate));
    }
    else {
        return QString("%1%2%3%4%5%6%7%8%9").arg(m_FilmID).arg(sepchar)
                .arg(m_Title).arg(sepchar).arg(m_Director).arg(sepchar).arg(m_FilmLength).arg(sepchar)
                .arg(m_ReleaseDate.toString(Qt::ISODate));
    }
}

//getter for ID
QString Film::getID()
{
    return m_FilmID;
}

//getter for Title
QString Film::getTitle()
{
    return m_Title;
}

//getter for Director
QString Film::getDirector()
{
    return m_Director;
}

//getter for length
quint32 Film::getFilmLength()
{
    return m_FilmLength;
}

//getter for release date
QDate Film::getReleaseDate()
{
    return m_ReleaseDate;
}
