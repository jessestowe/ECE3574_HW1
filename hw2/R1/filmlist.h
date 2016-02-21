#ifndef FILMLIST_H
#define FILMLIST_H

#include <QList>
#include <QStringList>
#include <typeinfo>
#include "film.h"

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
