/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: header file for bookUI class
 */

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
