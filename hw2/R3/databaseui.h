#ifndef DATABASEUI_H
#define DATABASEUI_H

#include "dvdui.h"

class DataBaseUI : public DvdUI
{
public:
    DataBaseUI();
    QStringList prompt();
};

#endif // DATABASEUI_H
