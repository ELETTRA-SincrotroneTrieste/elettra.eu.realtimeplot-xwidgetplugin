#-------------------------------------------------
#
# Project created by QtCreator 2019-09-03T15:28:56
#
#-------------------------------------------------

include(/usr/local/cumbia-libs/include/cumbia-qtcontrols/cumbia-qtcontrols.pri)

QT       += core gui

TARGET = elettra.eu.realtimeplot-xwidgetplugin
TEMPLATE = lib
CONFIG += plugin

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES -= QT_NO_DEBUG_OUTPUT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	src/qurtplot.cpp \
        src/elettra.eu.realtimeplot-xwidgetplugin.cpp

HEADERS += \
	src/qurtplot.h \
        src/elettra.eu.realtimeplot-xwidgetplugin.h

INC_PATH = $${INSTALL_ROOT}/include/qumbia-plugins
inc.files = src/qutextview.h
inc.path = $${INC_PATH}

DISTFILES += elettra.eu.realtimeplot-xwidgetplugin.json  \
    README.md

unix {
    target.path = $${DEFINES_CUMBIA_QTCONTROLS_PLUGIN_DIR}
    INSTALLS += target inc
}

message("elettra.eu.realtimeplot-xwidgetplugin: plugin installation dir:  $${DEFINES_CUMBIA_QTCONTROLS_PLUGIN_DIR}")
message("elettra.eu.realtimeplot-xwidgetplugin: include installation dir: $${INC_PATH}")
