# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = conf_app
DESTDIR = ../Debug
QT += core gui sql
CONFIG += debug
DEFINES += QT_LARGEFILE_SUPPORT QT_SQL_LIB
INCLUDEPATH += ./GeneratedFiles \
    ./GeneratedFiles/Debug \
    . \
    ./../app_new \
    $(BOOSTDIR)
LIBS += -L"."
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(conf_app.pri)
win32:RC_FILE = conf_app.rc
