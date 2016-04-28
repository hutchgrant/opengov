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


SOURCES += src/main.cpp \
    src/parsecsv.cpp \
    src/fileobj.cpp \
    src/control.cpp

HEADERS += \
    src/parsecsv.h \
    src/fileobj.h \
    src/control.h
