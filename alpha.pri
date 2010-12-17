#
# Base configuration
#

# Path configuration
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT       += gui

RESOURCES += i18n_alpha.qrc
TRANSLATIONS += \
    i18n_alpha/nl_BE.ts \
    i18n_alpha/en_US.ts
SOURCES += application.cpp \
    ui/maincontroller.cpp \
    ui/mainview.cpp \
    ui/liveboardcontroller.cpp \
    ui/liveboardview.cpp \
    ui/vehicleview.cpp \
    ui/vehiclecontroller.cpp \
    ui/connectioncontroller.cpp \
    ui/connectionview.cpp \
    ui/requestcontroller.cpp \
    ui/requestview.cpp \
    ui/genericview.cpp \
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

