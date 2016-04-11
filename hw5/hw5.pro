QT += core
QT -= gui

CONFIG += c++11

LIBS += -lrt

TARGET = hw5
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    manager.cpp

HEADERS += \
    manager.h
