#include "film.h"

Film::Film(QString id, QString title, QString dir, quint32 length, QDate relDate) : m_FilmID(id),
    m_Title(title), m_Director(dir), m_FilmLength(length), m_ReleaseDate(relDate)
{

}

Film::Film(QStringList propList) : m_FilmID(propList.takeFirst()), m_Title(propList.takeFirst()),
    m_Director(propList.takeFirst()), m_FilmLength(propList.takeFirst().toUInt()),
    m_ReleaseDate(QDate::fromString(propList.takeFirst(), Qt::ISODate))
{

}

Film::~Film()
{

}

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

QString Film::getID()
{
    return m_FilmID;
}

QString Film::getTitle()
{
    return m_Title;
}

QString Film::getDirector()
{
    return m_Director;
}

quint32 Film::getFilmLength()
{
    return m_FilmLength;
}

QDate Film::getReleaseDate()
{
    return m_ReleaseDate;
}
