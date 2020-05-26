
#-------------------------------------------------
#
# Project created by QtCreator 2020-5-1T08:19:18
#
#-------------------------------------------------

QT       += core gui xml multimedia
CONFIG += resources_big
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
LIBS += -LC:\Users\Administrator\Desktop\qtcode\gan\TowerDefense-master\lib
TARGET = Game
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    arrow.cpp \
    builtui.cpp \
    content.cpp \
    graph.cpp \
        main.cpp \
    map.cpp \
    range.cpp \
    road.cpp \
    levelparser.cpp \
    game.cpp \
    tower.cpp \
    enemy.cpp \
    level.cpp \
    towerui.cpp \
    hud.cpp \
    uiobject.cpp

HEADERS += \
    arrow.h \
    builtui.h \
    content.h \
    graph.h \
    map.h \
    range.h \
    road.h \
    levelparser.h \
    game.h \
    tower.h \
    enemy.h \
    level.h \
    towerui.h \
    hud.h \
    uiobject.h


RESOURCES += \
    res.qrc

DISTFILES +=
