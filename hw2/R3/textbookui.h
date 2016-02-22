/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: header file for TextBookUI class
 */


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
