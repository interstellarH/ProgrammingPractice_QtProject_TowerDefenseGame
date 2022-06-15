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
    select_button.cpp \
    select_button2.cpp \
    tower_position.cpp \
    waypoint.cpp

HEADERS  += mainwindow.h \
    auxiliary_function.h \
    bullet.h \
    defend_tower.h \
    enemy.h \
    select_button.h \
    select_button2.h \
    tower_position.h \
    waypoint.h

FORMS    += mainwindow.ui

RESOURCES += \
    rec.qrc
