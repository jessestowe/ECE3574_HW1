#ifndef FILMUI_H
#define FILMUI_H

#include "dvdui.h"

class FilmUI : public DvdUI
{
public:
    FilmUI();
    QStringList prompt();
};

#endif // FILMUI_H
