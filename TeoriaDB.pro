#-------------------------------------------------
#
# Project created by QtCreator 2014-08-08T20:38:17
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TeoriaDB
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    logreader.cpp \
    hexmanager.cpp \
    registerrestorer.cpp \
    bytecaster.cpp \
    fielddesccriptor.cpp \
    numeric.cpp \
    connectgui.cpp \
    columnstructure.cpp

HEADERS  += mainwindow.h \
    logreader.h \
    hexmanager.h \
    registerrestorer.h \
    bytecaster.h \
    fielddesccriptor.h \
    numeric.h \
    connectgui.h \
    columnstructure.h

FORMS    += mainwindow.ui \
    registerrestorer.ui \
    fielddesccriptor.ui \
    connectgui.ui

RESOURCES += \
    Orange.qrc
