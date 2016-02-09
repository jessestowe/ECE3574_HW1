#ifndef ENTERTAINMENT_H
#define ENTERTAINMENT_H

#include "film.h"

enum FilmTypes { Action, Comedy, SciFi, Drama, Romantic };
enum MPAARatings { G, PG, PG13, R };

class Entertainment: public Film
{
public:
    Entertainment(QString id, QString title, QString dir, quint32 len,
                  QDate relDate, FilmTypes type, MPAARatings rtng);
    Entertainment(QStringList propList);
    QString toString(bool labeled, QString sepchar);
private:
    FilmTypes m_Type;
    MPAARatings m_Rating;
};

#endif // ENTERTAINMENT_H
