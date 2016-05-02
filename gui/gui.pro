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
            src/jsondisplay.cpp \
    src/options.cpp \
    src/base.cpp

HEADERS  += \
            src/jsondisplay.h \
    src/options.h \
    src/base.h

FORMS    += \
            src/jsondisplay.ui \
    src/options.ui \
    src/base.ui

INCLUDEPATH += ../opengov-lib
LIBS += -L../opengov-lib -lopengov-lib

DESTDIR = ../
