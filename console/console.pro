#-------------------------------------------------
#
# Project created by QtCreator 2016-04-25T16:03:49
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = opengov
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += src/control.cpp \
            src/main.cpp

HEADERS += src/control.h \
            src/main.h

INCLUDEPATH += ../opengov-lib
LIBS += -L../opengov-lib -lopengov-lib

DESTDIR = ../
