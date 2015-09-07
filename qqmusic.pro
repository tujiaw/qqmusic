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
    src/dialog.cpp \
    src/itemlist.cpp \
    src/netmanager.cpp \
    src/player.cpp \
    src/model/request.cpp \
    src/model/response.cpp \
    src/tools/json.cpp \
    src/widget/drop_widget.cpp \
    src/widget/pagenumberwidget.cpp \
    src/widget/pic_button.cpp

HEADERS  += \
    src/dialog.h \
    src/itemlist.h \
    src/netmanager.h \
    src/player.h \
    src/model/request.h \
    src/model/response.h \
    src/tools/json.h \
    src/widget/drop_widget.h \
    src/widget/pagenumberwidget.h \
    src/widget/pic_button.h

FORMS    += src/dialog.ui

RESOURCES += rc/rc.qrc

DISTFILES += \
    src/README.md \
    rc/itemlist.txt \
    rc/style.qss \
    rc/images/ou_mei.jpg \
    rc/images/close.png \
    rc/images/next.png \
    rc/images/pause.png \
    rc/images/play.png \
    rc/images/prev.png \
    rc/images/stop.png

