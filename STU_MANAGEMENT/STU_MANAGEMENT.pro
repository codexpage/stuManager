#-------------------------------------------------
#
# Project created by QtCreator 2015-10-05T21:20:53
#
#-------------------------------------------------

QT       += core gui
QT      +=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = STU_MANAGEMENT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    studentwindow.cpp \
    teacherwindow.cpp

HEADERS  += mainwindow.h \
    studentwindow.h \
    teacherwindow.h \
    database.h

FORMS    += mainwindow.ui \
    studentwindow.ui \
    teacherwindow.ui

RESOURCES += \
    resource.qrc

DISTFILES +=
