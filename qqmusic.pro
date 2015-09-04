#-------------------------------------------------
#
# Project created by QtCreator 2015-09-03T16:36:58
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += multimedia

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qqmusic
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    json.cpp \
    request.cpp \
    response.cpp \
    itemlist.cpp \
    player.cpp \
    netmanager.cpp \
    pagenumberwidget.cpp

HEADERS  += dialog.h \
    json.h \
    request.h \
    response.h \
    itemlist.h \
    player.h \
    netmanager.h \
    pagenumberwidget.h

FORMS    += dialog.ui

RESOURCES += \
    rc.qrc
