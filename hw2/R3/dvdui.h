#ifndef DVDUI_H
#define DVDUI_H

#include "refitemui.h"

class DvdUI : public RefItemUI
{
public:
    DvdUI();
    QStringList prompt();
};

#endif // DVDUI_H
