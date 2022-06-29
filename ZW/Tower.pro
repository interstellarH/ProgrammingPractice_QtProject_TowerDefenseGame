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
    bullet.cpp \
    defend_tower.cpp \
    enemy.cpp \
        mainwindow.cpp \
    selectbutton.cpp \
    selectbutton2.cpp \
    start.cpp \
    towerposition.cpp \
    waypoint.cpp

HEADERS  += mainwindow.h \
    auxiliary_function.h \
    bullet.h \
    defend_tower.h \
    enemy.h \
    selectbutton.h \
    selectbutton2.h \
    start.h \
    towerposition.h \
    waypoint.h

FORMS    += mainwindow.ui \
    start.ui

RESOURCES += \
    resource1.qrc
