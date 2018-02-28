TARGET = telescoped
CONFIG   += console C++11

load(ubuntu-click)

QT       += core bluetooth dbus
QT       -= gui

include(../version.pri)
include(libasteroid/libasteroid.pri)

TEMPLATE = app

SOURCES += utouch_main.cpp \ 
    $$PWD/dbusinterface.cpp \
    $$PWD/ubuntuplatform.cpp \
    $$PWD/watchesmanager.cpp \
    bluez/bluezclient.cpp \
    bluez/bluez_agentmanager1.cpp \
    bluez/bluez_adapter1.cpp \
    bluez/bluez_device1.cpp \
    bluez/freedesktop_objectmanager.cpp \
    bluez/freedesktop_properties.cpp


# Default rules for deployment.
target.path = $${UBUNTU_CLICK_BINARY_PATH}
INSTALLS+=target

HEADERS += \
    $$PWD/dbusinterface.h \
    $$PWD/ubuntuplatform.h \
    $$PWD/watchesmanager.h \
    bluez/bluezclient.h \
    bluez/bluez_agentmanager1.h \
    bluez/bluez_adapter1.h \
    bluez/bluez_device1.h \
    bluez/freedesktop_objectmanager.h \
    bluez/freedesktop_properties.h
