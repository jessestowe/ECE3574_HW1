QT += core
QT -= gui

CONFIG += c++11

TARGET = R2
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    libraryClient-v2.cpp \
    library.cpp \
    libraryui.cpp

HEADERS += \
    library.h \
    libraryui.h
