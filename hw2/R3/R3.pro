QT += core
QT -= gui

CONFIG += c++11

TARGET = R3
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    libraryui.cpp \
    libraryClient-v2.cpp \
    library.cpp \
    refitemui.cpp \
    bookui.cpp \
    referencebookui.cpp \
    textbookui.cpp \
    dvdui.cpp \
    filmui.cpp \
    databaseui.cpp

HEADERS += \
    libraryui.h \
    library.h \
    refitemui.h \
    bookui.h \
    referencebookui.h \
    textbookui.h \
    dvdui.h \
    filmui.h \
    databaseui.h
