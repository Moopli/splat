#-------------------------------------------------
#
# Project created by QtCreator 2014-08-28T12:43:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Splat
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    ../../../Downloads/splat/opcodeProcessing.cpp \
    ../../../Downloads/splat/stateData.cpp

HEADERS  += mainwindow.h \
    ../../../Downloads/splat/opcodeProcessing.h \
    ../../../Downloads/splat/stateData.h \
    ../../../Downloads/splat/loadRom.h

FORMS    += mainwindow.ui

LIBS += -lX11
