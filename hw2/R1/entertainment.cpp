/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: class definition file for Entertainment derived class of Film
 */

#include "entertainment.h"

//constructor for Entertainment class with individual params
Entertainment::Entertainment(QString id, QString title, QString dir, quint32 len,
                             QDate relDate, FilmTypes type, MPAARatings rtng) :
    Film(id, title, dir, len, relDate), m_Type(type), m_Rating(rtng)
{

}

//constructor for Entertainment class with QStringList param
Entertainment::Entertainment(QStringList& propList) : Film(propList)
{
    //convert string to enum for film type
    QString type = propList.takeFirst();
    if(type == "Action") {
            m_Type = Action;
    }
    else if(type == "Comedy") {
        m_Type = Comedy;
    }
    else if(type == "SciFi") {
        m_Type = SciFi;
    }
    else if(type == "Drama") {
        m_Type = Drama;
    }
    else if(type == "Romantic") {
        m_Type = Romantic;
    }
    else {
        //throw exception on invalid input
        throw std::invalid_argument("Invalid type");
    }
    //convert string to enum for rating
    QString rating = propList.takeFirst();
    //{ G, PG, PG13, R };
    if(rating == "G") {
        m_Rating = G;
    }
    else if(rating == "PG") {
        m_Rating = PG;
    }
    else if(rating == "PG13") {
        m_Rating = PG13;
    }
    else if(rating == "R") {
        m_Rating = R;
    }
    else {
        //throw exception on invalid input
        throw std::invalid_argument("Invalid rating");
    }
}

//returns a QString with all of the information from the film with sepchar and labels if specified
QString Entertainment::toString(bool labeled, QString sepchar) const
{
    if(labeled) {
        return QString("%1%2%3%4%5%6%7").arg(Film::toString(labeled, sepchar)).arg(sepchar).arg("Type: ")
                .arg(FilmTypeStrings[m_Type]).arg(sepchar).arg("Rating: ").arg(MPAARatingStrings[m_Rating]);
    }
    else {
        return QString("%1%2%3%4%5").arg(Film::toString(labeled, sepchar)).arg(sepchar)
                .arg(FilmTypeStrings[m_Type]).arg(sepchar).arg(MPAARatingStrings[m_Rating]);
    }
}

//getter for film type
FilmTypes Entertainment::getFilmType()
{
    return m_Type;
}

//getter for rating
MPAARatings Entertainment::getRating()
{
    return m_Rating;
}
