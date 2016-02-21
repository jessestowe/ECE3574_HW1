#ifndef ENTERTAINMENT_H
#define ENTERTAINMENT_H

#include "film.h"

enum FilmTypes { Action = 0, Comedy, SciFi, Drama, Romantic };
static const char * FilmTypeStrings[] = { "Action", "Comedy", "SciFi", "Drama", "Romantic" };
enum MPAARatings { G = 0, PG, PG13, R };
static const char * MPAARatingStrings[] = { "G", "PG", "PG13", "R" };

class Entertainment: public Film
{
public:
    Entertainment(QString id, QString title, QString dir, quint32 len,
                  QDate relDate, FilmTypes type, MPAARatings rtng);
    Entertainment(QStringList propList);
    QString toString(bool labeled, QString sepchar) const;
    FilmTypes getFilmType();
    MPAARatings getRating();
private:
    FilmTypes m_Type;
    MPAARatings m_Rating;
};

#endif // ENTERTAINMENT_H
