#include "filmlist.h"

FilmList::FilmList()
{

}

FilmList::~FilmList()
{
    qDeleteAll(*this);
    clear();
}

FilmList::FilmList(const FilmList &) : QList<Film*>()
{

}

FilmList& FilmList::operator=(const FilmList&)
{
    return *this;
}

QString FilmList::toString()
{
    QString ret;
    for(int i = 0; i < this->size(); ++i) {
        ret.append(this->at(i)->toString(false, "[::]").append("\n"));
    }
    return ret;
}

void FilmList::addFilm(Film *film)
{
    Film* ref = findFilm(film->getID());
    if(ref) {
        //check for film with same params
        for(int i = 0; i < size(); ++i) {
            Film* current = at(i);
            //check for all desired fields which are considered to make a film duplicate
            //possible to also use contains here with override of film == operator
            if(current->getTitle() == film->getTitle()
                    && current->getDirector() == film->getDirector()
                    && current->getFilmLength() == film->getFilmLength()
                    && current->getReleaseDate() == film->getReleaseDate()
                    && typeid(current) == typeid(film)) {
                throw std::invalid_argument("List already contains film with given parameters");
            }
        }
        //no duplicates in list, add to list
        append(film);
    }
    //found film with identical id, throw exception
    else {
        throw std::invalid_argument("List already contains film with given id");
    }
}

Film* FilmList::findFilm(QString id)
{
    for(int i = 0; i < size(); ++i) {
        if(at(i)->getID().trimmed() == id.trimmed()) {
            return at(i);
        }
    }
    return 0;
}

QStringList FilmList::getID(QString title)
{
    QStringList ret;
    for(int i = 0; i < size(); ++i) {
        if(at(i)->getTitle().trimmed() == title.trimmed()) {
            ret.append(at(i)->getID());
        }
    }
    return ret;
}

void FilmList::removeFilm(QString filmID)
{
    Film* ref = findFilm(filmID);
    if(ref) {
        removeAll(ref);
        delete ref;
    }
    else {
        throw std::range_error("Cannot find film to be deleted");
    }
}
