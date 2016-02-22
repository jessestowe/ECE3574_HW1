/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: header file for ReferenceBookUI class
 */

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
