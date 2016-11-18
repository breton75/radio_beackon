#-------------------------------------------------
#
# Project created by QtCreator 2016-02-29T10:08:52
#
#-------------------------------------------------

QT       += core gui xml sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = beacon_2
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    sv_area.cpp \
    ../../../Common/sv_settings.cpp \
    sv_beackonsymbol.cpp \
    converting.cpp \
    sv_mapobjects.cpp \
    ../../../Common/sv_sqlite.cpp \
    sv_udpstream.cpp \
    sv_beaconeditor.cpp

HEADERS  += mainwindow.h \
    sv_area.h \
    ../../../Common/sv_settings.h \
    sv_beackonsymbol.h \
    converting.h \
    sv_mapobjects.h \
    ../../../Common/sv_sqlite.h \
    sv_udpstream.h \
    sv_beaconeditor.h

INCLUDEPATH += ../../../Common

FORMS    += mainwindow.ui \
    sv_beaconeditor.ui

RESOURCES += \
    res.qrc
