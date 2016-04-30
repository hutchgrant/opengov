#-------------------------------------------------
#
# Project created by QtCreator 2016-04-29T19:42:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opengov-gui
TEMPLATE = app


SOURCES += src/main.cpp \
        src/mainwindow.cpp

HEADERS  += src/mainwindow.h

FORMS    += src/mainwindow.ui

INCLUDEPATH += ../opengov-lib
LIBS += -L../opengov-lib -lopengov-lib

DESTDIR = ../
