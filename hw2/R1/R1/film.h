#ifndef FILM_H
#define FILM_H

#include <QDate>
#include <QString>
#include <QStringList>

class Film
{
public:
    Film(QString id, QString title, QString dir, quint32 length, QDate relDate);
    Film(QStringList propList);
    QString virtual toString(bool labeled, QString sepchar);
private:
    QString m_FilmID;
    QString m_Title;
    QString m_Director;
    quint32 m_FilmLength;
    QDate m_ReleaseDate;
};

#endif // FILM_H
