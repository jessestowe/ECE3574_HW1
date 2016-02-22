#ifndef REFITEMUI_H
#define REFITEMUI_H

#include <QStringList>
#include <QDate>
#include "library.h"

extern QTextStream m_cout;
extern QTextStream m_cin;

class RefItemUI
{
public:
    RefItemUI();
    virtual ~RefItemUI();
    QStringList prompt();
};

#endif // REFITEMUI_H
