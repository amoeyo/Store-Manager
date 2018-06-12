#-------------------------------------------------
#
# Project created by QtCreator 2018-06-12T15:57:17
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       +=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += console
