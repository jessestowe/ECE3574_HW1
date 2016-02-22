#ifndef BOOKUI_H
#define BOOKUI_H

#include "refitemui.h"

class BookUI: public RefItemUI
{
public:
    BookUI();
    QStringList prompt();
};

#endif // BOOKUI_H
