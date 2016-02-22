#ifndef REFERENCEBOOKUI_H
#define REFERENCEBOOKUI_H

#include "bookui.h"

class ReferenceBookUI : public BookUI
{
public:
    ReferenceBookUI();
    QStringList prompt();
};

#endif // REFERENCEBOOKUI_H
