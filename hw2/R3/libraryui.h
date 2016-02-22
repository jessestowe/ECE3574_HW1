/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: header file for libraryUI class
 */

#ifndef LIBRARYUI_H
#define LIBRARYUI_H

#include <QString>
#include <QStringList>
#include <QTextStream>
#include <iostream>
#include <QFile>
#include <QDate>
#include <QDebug>
#include "library.h"
#include "bookui.h"
#include "referencebookui.h"
#include "textbookui.h"
#include "dvdui.h"
#include "filmui.h"
#include "databaseui.h"

class LibraryUI
{
public:
    LibraryUI();
    LibraryUI(Library* lib);
    void add(QStringList objdata);
    void read();
    void enterData();
    QString find();
    void remove();
    void save();
    void list();
    QStringList promptRefItem();
    QStringList promptBook();
    QStringList promptReferenceBook();
    QStringList promptTextBook();
    QStringList promptDvd();
    QStringList promptFilm();
    QStringList promptDataBase();
    enum Choices {READ=1, ADD, FIND, REMOVE, SAVE, LIST, QUIT};
    enum Types {BOOK, REFERENCEBOOK, TEXTBOOK, DVD, FILM, DATADVD};
    Choices nextTask();
    void prepareToQuit(bool saved);
private:
    Library* m_Lib;
    const QStringList TYPES = (QStringList() << "BOOK" << "REFERENCEBOOK"
                              << "TEXTBOOK" << "DVD" << "FILM" << "DATADVD");
    bool saved;
};

#endif // LIBRARYUI_H
