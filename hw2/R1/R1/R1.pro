QT += core
QT -= gui

CONFIG += c++11

TARGET = R1
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    film.cpp \
    educational.cpp \
    entertainment.cpp

HEADERS += \
    film.h \
    educational.h \
    entertainment.h
