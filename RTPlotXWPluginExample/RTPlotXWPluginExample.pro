include (/usr/local/cumbia-libs/include/qumbia-tango-controls/qumbia-tango-controls.pri)

TEMPLATE = app

QT +=  core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets x11extras

CONFIG +=


CONFIG+=link_pkgconfig
PKGCONFIG += x11

DEFINES += QT_NO_DEBUG_OUTPUT

OBJECTS_DIR = obj

# RESOURCES +=


SOURCES += src/main.cpp \
    src/RTPlotXWPluginExample.cpp

HEADERS += \
    src/RTPlotXWPluginExample.h

# cuuimake runs uic
# FORMS    = src/TextViewXWPluginExample.ui
# but we need to include ui_xxxx.h file amongst the headers
# in order to be recompiled when it changes
#
#HEADERS += \
#    ui/ui_TextViewXWPluginExample.h

# - ui: where to find cuuimake ui_*.h files
#   since FORMS is not used
# - src: where to find headers included by
#   ui_*.h (e.g. for custom widget promoted
#   from the Qt designer)
#
INCLUDEPATH += ui src

TARGET   = bin/RTPlotXWPluginExample

# unix:LIBS += -L. -lmylib

# unix:INCLUDEPATH +=  . ../../src

message("")
message("NOTE")
message("You need to run cuuimake in order to build the project")
message("")
message("        cuuimake --show-config to see cuuimake configuration options")
message("        cuuimake --configure to configure cuuimake")
message("        cuuimake -jN to execute cuuimake and then make -jN")
message("        cuuimake --make to run cuuimake and then make")
message("")
