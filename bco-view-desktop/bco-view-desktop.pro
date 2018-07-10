#-------------------------------------------------
#
# Project created by QtCreator 2018-07-07T18:16:54
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bco-view-desktop
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


SOURCES += \
        main.cpp \
        MainWindow.cpp \
    PrescriptionOrderWidget.cpp \
    PrescriptionBatchWidget.cpp

HEADERS += \
        MainWindow.h \
    PrescriptionOrderWidget.h \
    PrescriptionBatchWidget.h

FORMS += \
        MainWindow.ui \
    PrescriptionOrderWidget.ui \
    PrescriptionBatchWidget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../bco-view-core/release/ -lbco-view-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../bco-view-core/debug/ -lbco-view-core

INCLUDEPATH += $$PWD/../bco-view-core
DEPENDPATH += $$PWD/../bco-view-core