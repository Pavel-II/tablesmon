#-------------------------------------------------
#
# Project created by QtCreator 2017-11-21T16:22:50
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tablesmon
#
TRANSLATIONS = tsm_ru_RU.ts
#
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
        tsm_mw.cpp \
    tsm_cd.cpp \
    sqlsyntaxhighlighter.cpp \
    tsm_w.cpp \
    tsm_settings.cpp \
    tsm_w_sb.cpp

HEADERS += \
        tsm_mw.h \
    tsm_cd.h \
    sqlsyntaxhighlighter.h \
    tsm_w.h \
    tsm_settings.h \
    tsm_w_sb.h

FORMS += \
        tsm_mw.ui \
    tsm_cd.ui \
    tsm_w.ui \
    tsm_settings.ui \
    tsm_w_sb.ui

RESOURCES += \
    icons.qrc
