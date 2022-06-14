#-------------------------------------------------
#
# Project created by QtCreator 2022-06-14T08:43:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tower
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    waypoint.cpp

HEADERS  += mainwindow.h \
    waypoint.h

FORMS    += mainwindow.ui

RESOURCES += \
    rec.qrc
