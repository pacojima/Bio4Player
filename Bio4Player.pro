#-------------------------------------------------
#
# Project created by QtCreator 2015-10-12T02:01:37
#
#-------------------------------------------------

CONFIG += c++11

RC_ICONS = resource/b4p_icon.ico

QT += core gui
QT += webkitwidgets
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bio4Player
TEMPLATE = app


SOURCES += \
    source/main.cpp \
    userinterface/b4p_mainwindow.cpp \
    userinterface/b4p_liveitem.cpp \
    userinterface/b4p_loginwindow.cpp \
    source/b4p_playermanager.cpp \
    source/b4p_login.cpp \
    source/b4p_heartbeat.cpp \
    source/b4p_livesearcher.cpp \
    userinterface/b4p_viewpanel.cpp

HEADERS  += \
    userinterface/b4p_mainwindow.h \
    userinterface/b4p_liveitem.h \
    userinterface/b4p_loginwindow.h \
    source/b4p_playermanager.h \
    source/b4p_login.h \
    source/b4p_heartbeat.h \
    source/b4p_livesearcher.h \
    userinterface/b4p_viewpanel.h

FORMS    += \
    userinterface/b4p_mainwindow.ui \
    userinterface/b4p_liveitem.ui \
    userinterface/b4p_loginwindow.ui \
    userinterface/b4p_viewpanel.ui

RESOURCES += \
    resource/resource.qrc
