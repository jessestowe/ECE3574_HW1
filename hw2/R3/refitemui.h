/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: header file for RefItemUI class
 */


#ifndef REFITEMUI_H
#define REFITEMUI_H

#include <QStringList>
#include <QDate>
#include "library.h"

//use extern so that the linker can find m_cout and m_cin
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
