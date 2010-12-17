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
    ui/screens/maincontroller.cpp \
    ui/screens/mainview.cpp \
    ui/screens/liveboardcontroller.cpp \
    ui/screens/liveboardview.cpp \
    ui/screens/vehicleview.cpp \
    ui/screens/vehiclecontroller.cpp \
    ui/screens/connectioncontroller.cpp \
    ui/screens/connectionview.cpp \
    ui/screens/requestcontroller.cpp \
    ui/screens/requestview.cpp \
    ui/screens/genericview.cpp \
    ui/screens/genericcontroller.cpp
HEADERS += application.h \
    ui/global.h \
    ui/screens/maincontroller.h \
    ui/screens/mainview.h \
    ui/screens/liveboardcontroller.h \
    ui/screens/liveboardview.h \
    ui/screens/vehicleview.h \
    ui/screens/vehiclecontroller.h \
    ui/screens/connectioncontroller.h \
    ui/screens/connectionview.h \
    ui/screens/requestcontroller.h \
    ui/screens/requestview.h \
    ui/screens/genericview.h \
    ui/screens/genericcontroller.h

