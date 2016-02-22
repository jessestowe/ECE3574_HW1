/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: header file for FilmList, which derives from QList<Film*> and contains a list of films
 */

#ifndef FILMLIST_H
#define FILMLIST_H

#include <QList>
#include <QStringList>
#include <typeinfo>
#include "film.h"
#include "educational.h"
#include "entertainment.h"

class FilmList : public QList<Film*>
{
public:
    FilmList();
    ~FilmList();
    QString toString();
    Film* findFilm(QString id);
    QStringList getID(QString title);
    void addFilm(Film* film);
    void removeFilm(QString filmID);
private:
    FilmList(const FilmList&);
    FilmList& operator=(const FilmList&);
};

#endif // FILMLIST_H
