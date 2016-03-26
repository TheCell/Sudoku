QT += core
QT -= gui

TARGET = Sudoku
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    sudokugenerator.cpp \
    gamemgr.cpp \
    randomengine.cpp

HEADERS += \
    sudokugenerator.h \
    gamemgr.h \
    randomengine.h

DISTFILES += \
    Sudoku.pro.user

