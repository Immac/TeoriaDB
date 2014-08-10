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
    hexmanager.cpp

HEADERS  += mainwindow.h \
    logreader.h \
    hexmanager.h

FORMS    += mainwindow.ui
