# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

# This is a reminder that you are using a generated .pro file.
# Remove it when you are finished editing this file.
message("You are running qmake on a generated .pro file. This may not work!")


TEMPLATE = app
TARGET = app_new
DESTDIR = ../Debug
QT += core gui sql network xml script xmlpatterns qtmain webkit
CONFIG += qtestlib debug
DEFINES += QT_LARGEFILE_SUPPORT QT_XML_LIB QT_SQL_LIB QT_XMLPATTERNS_LIB QT_SCRIPT_LIB
INCLUDEPATH += ./GeneratedFiles \
    ./GeneratedFiles/Debug \
    . \
    $(BOOSTDIR) \
    $(PROJDIR)/customctrl_solution/CustomTimeCtrl \
    $(PROJDIR)/customctrl_solution/CustomTimeCtrl/GeneratedFiles \
    $(PROJDIR)/CatchInputCtrl/CatchInputCtrl \
    $(PROJDIR)/CatchInputCtrl/CatchInputCtrl/GeneratedFiles \
    $(EXARO_INCLUDE_DIR)
LIBS += -L"$(QTDIR)/plugins/designer" \
    -L"$(EXARO_LIBRARIES)" \
    -lcustomtimectrld \
    -lCatchInputCtrld \
    -lReportd
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(app_new.pri)
TRANSLATIONS += ./app_new_pt.ts
win32:RC_FILE = app_new.rc
