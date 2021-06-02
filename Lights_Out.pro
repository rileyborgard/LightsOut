#-------------------------------------------------
#
# Project created by QtCreator 2016-06-01T11:55:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lights_Out
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    boardwidget.cpp \
    gaussianelimination.cpp

HEADERS  += mainwindow.h \
    boardwidget.h \
    gaussianelimination.h

CONFIG += static
