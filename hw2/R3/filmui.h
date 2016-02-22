/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: header file for filmUI class
 */

#ifndef FILMUI_H
#define FILMUI_H

#include "dvdui.h"

class FilmUI : public DvdUI
{
public:
    FilmUI();
    QStringList prompt();
};

#endif // FILMUI_H
