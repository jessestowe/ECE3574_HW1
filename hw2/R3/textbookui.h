#ifndef TEXTBOOKUI_H
#define TEXTBOOKUI_H

#include "bookui.h"

class TextBookUI : public BookUI
{
public:
    TextBookUI();
    QStringList prompt();
};

#endif // TEXTBOOKUI_H
