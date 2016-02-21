#include "educational.h"

Educational::Educational(QString id, QString title, QString dir, quint32 len, QDate relDate, QString subject, Grade grade) : Film(id, title, dir, len, relDate),
    m_Subject(subject), m_GradeLevel(grade)
{

}

Educational::Educational(QStringList propList) : Film(propList),
    m_Subject(propList.takeFirst()), m_GradeLevel(propList.takeFirst().toUInt())
{

}

QString Educational::toString(bool labeled, QString sepchar) const
{
    if(labeled) {
        return QString("%1%2%3%4%5%6%7").arg(Film::toString(labeled, sepchar)).arg(sepchar)
                .arg("Subject: ").arg(m_Subject).arg(sepchar).arg("Grade: ").arg(m_GradeLevel);
    }
    else {
        return QString("%1%2%3%4%5").arg(Film::toString(labeled, sepchar))
                .arg(sepchar).arg(m_Subject).arg(sepchar).arg(m_GradeLevel);
    }
}

QString Educational::getSubject()
{
    return m_Subject;
}

Grade Educational::getGradeLevel()
{
    return m_GradeLevel;
}
