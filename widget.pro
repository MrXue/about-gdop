#-------------------------------------------------
#
# Project created by QtCreator 2015-12-27T16:02:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = widget
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    readaccess.cpp \
    savecount.cpp \
    n1variationtrend.cpp \
    readaer.cpp \
    gdop.cpp

HEADERS  += widget.h \
    readaccess.h \
    savecount.h \
    n1variationtrend.h \
    readaer.h \
    gdop.h

FORMS    += widget.ui \
    n1variationtrend.ui
