#
# Base configuration
#

# Path configuration
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT       += gui

RESOURCES += ui.qrc \
    translations.qrc
SOURCES += application.cpp \
    ui/screens/maincontroller.cpp \
    ui/dialogs/stationchooser.cpp \
    ui/auxiliary/delegates/connectiondelegate.cpp \
    ui/auxiliary/delegates/connectionpoidelegate.cpp \
    ui/auxiliary/delegates/vehiclestopdelegate.cpp \
    ui/auxiliary/delegates/liveboarddeparturedelegate.cpp \
    ui/screens/mainview.cpp \
    ui/screens/liveboardcontroller.cpp \
    ui/screens/liveboardview.cpp \
    ui/screens/vehicleview.cpp \
    ui/screens/vehiclecontroller.cpp \
    ui/screens/connectioncontroller.cpp \
    ui/screens/connectionview.cpp \
    ui/screens/requestcontroller.cpp \
    ui/screens/requestview.cpp \
    ui/auxiliary/loaderwidget.cpp \
    ui/screens/genericview.cpp \
    ui/dialogs/about.cpp \
    ui/auxiliary/delegates/requestdelegate.cpp \
    ui/screens/genericcontroller.cpp
HEADERS += \
    ui/global.h \
    ui/screens/maincontroller.h \
    ui/dialogs/stationchooser.h \
    ui/auxiliary/delegates/connectiondelegate.h \
    ui/auxiliary/delegates/connectionpoidelegate.h \
    ui/auxiliary/delegates/vehiclestopdelegate.h \
    ui/auxiliary/delegates/liveboarddeparturedelegate.h \
    ui/screens/mainview.h \
    ui/screens/liveboardcontroller.h \
    ui/screens/liveboardview.h \
    ui/screens/vehicleview.h \
    ui/screens/vehiclecontroller.h \
    ui/screens/connectioncontroller.h \
    ui/screens/connectionview.h \
    ui/screens/requestcontroller.h \
    ui/screens/requestview.h \
    ui/auxiliary/loaderwidget.h \
    ui/screens/genericview.h \
    ui/auxiliary/animationwidget.h \
    ui/auxiliary/animationrectitem.h \
    ui/auxiliary/graphicsrectobject.h \
    application.h \
    ui/dialogs/about.h \
    ui/auxiliary/delegates/requestdelegate.h \
    ui/screens/genericcontroller.h
TRANSLATIONS += \
    translations/nl_BE.ts \
    translations/en_US.ts

