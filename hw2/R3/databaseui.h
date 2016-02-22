/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: header file for DataBaseUI class
 */


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
