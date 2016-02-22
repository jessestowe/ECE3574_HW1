/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: header file for DvdUI class
 */

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
