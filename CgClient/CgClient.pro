#-------------------------------------------------
#
# Project created by QtCreator 2018-06-12T17:36:20
#
#-------------------------------------------------

QT       += core gui
QT       += network
CONFIG   += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CgClient
TEMPLATE = app


SOURCES += main.cpp \
    login.cpp

HEADERS  += \
    login.h

FORMS    += \
    login.ui
