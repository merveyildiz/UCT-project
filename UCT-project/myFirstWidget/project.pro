#-------------------------------------------------
#
# Project created by QtCreator 2015-02-25T21:11:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    draglabel.cpp \
    slottable.cpp

HEADERS  += mainwindow.h \
    draglabel.h \
    slottable.h \
    global.h \
    rand.h \
    epsmoea.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

DISTFILES +=
