#-------------------------------------------------
#
# Project created by QtCreator 2021-05-31T13:00:22
#
#-------------------------------------------------

QT       += core gui
QT      += network
QT      += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rdet_gui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        extensionssubscripts.cpp \
        libsubscripts.cpp \
        main.cpp \
        mainwindow.cpp \
        metahandler.cpp \
        rdetlogshandler.cpp \
        settings.cpp \
        xmlfilehandler.cpp

HEADERS += \
        extensionssubscripts.h \
        libsubscripts.h \
        mainwindow.h \
        metahandler.h \
        rdetlogshandler.h \
        settings.h \
        xmlfilehandler.h

FORMS += \
        mainwindow.ui \
        settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
