#
# Base configuration
#

# Path configuration
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include(../libirail/libirail.pri)

QT       += gui

RESOURCES += i18n_alpha.qrc
TRANSLATIONS += \
    i18n_alpha/nl.ts \
    i18n_alpha/fr.ts \
    i18n_alpha/de.ts \
    i18n_alpha/en.ts
SOURCES += application.cpp \
    ui/maincontroller.cpp \
    ui/liveboardcontroller.cpp \
    ui/vehiclecontroller.cpp \
    ui/connectioncontroller.cpp \
    ui/requestcontroller.cpp \
    ui/genericcontroller.cpp
HEADERS += application.h \
    ui/global.h \
    ui/maincontroller.h \
    ui/mainview.h \
    ui/liveboardcontroller.h \
    ui/liveboardview.h \
    ui/vehicleview.h \
    ui/vehiclecontroller.h \
    ui/connectioncontroller.h \
    ui/connectionview.h \
    ui/requestcontroller.h \
    ui/requestview.h \
    ui/genericview.h \
    ui/genericcontroller.h

