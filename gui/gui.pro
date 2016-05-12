#-------------------------------------------------
#
# Project created by QtCreator 2016-04-29T19:42:15
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opengov-gui
TEMPLATE = app

include(src/html5applicationviewer/html5applicationviewer.pri)
qtcAddDeployment()

SOURCES += src/main.cpp \
            src/jsondisplay.cpp \
    src/options.cpp \
    src/base.cpp \
    src/exportdialog.cpp \
    src/detached.cpp

HEADERS  += \
            src/jsondisplay.h \
    src/options.h \
    src/base.h \
    src/exportdialog.h \
    src/detached.h

FORMS    += \
            src/jsondisplay.ui \
    src/options.ui \
    src/base.ui \
    src/exportdialog.ui \

INCLUDEPATH += ../opengov-lib
LIBS += -L../opengov-lib -lopengov-lib

DESTDIR = ../

RESOURCES += \
    res/ogRes.qrc
