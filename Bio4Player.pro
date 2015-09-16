#-------------------------------------------------
#
# Project created by QtCreator 2015-09-07T13:48:21
#
#-------------------------------------------------

CONFIG += c++11

RC_ICONS = resource/b4p_icon.ico

QT       += core gui
QT += webkitwidgets
QT += network
QT += sql
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bio4Player
TEMPLATE = app


SOURCES += src/main.cpp\
        ui/b4p_mainwindow.cpp \
    src/Bio4PlayerLib/b4p_playermanager.cpp \
    ui/b4p_settingwindow.cpp \
    src/Bio4PlayerLib/b4p_setting.cpp \
    src/Bio4PlayerLib/b4p_nicookie.cpp \
    src/Bio4PlayerLib/b4p_bio4searcher.cpp \
    src/Bio4PlayerLib/b4p_livedata.cpp \
    ui/b4p_bio4listitem.cpp \
    ui/b4p_livewindow.cpp

HEADERS  += ui/b4p_mainwindow.h \
    src/Bio4PlayerLib/b4p_playermanager.h \
    ui/b4p_settingwindow.h \
    src/Bio4PlayerLib/b4p_setting.h \
    src/Bio4PlayerLib/b4p_nicookie.h \
    src/Bio4PlayerLib/b4p_bio4searcher.h \
    src/Bio4PlayerLib/b4p_livedata.h \
    ui/b4p_bio4listitem.h \
    ui/b4p_livewindow.h

FORMS    += ui/b4p_mainwindow.ui \
    ui/b4p_settingwindow.ui \
    ui/b4p_bio4listitem.ui \
    ui/b4p_livewindow.ui

RESOURCES += \
    resource/b4p_icons.qrc
