QT += core
QT -= gui

CONFIG += c++11

TARGET = R1
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    film.cpp \
    educational.cpp \
    entertainment.cpp \
    filmlist.cpp \
    filmListClient.cpp

HEADERS += \
    film.h \
    educational.h \
    entertainment.h \
    filmlist.h
