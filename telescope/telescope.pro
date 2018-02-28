TEMPLATE = app
TARGET = telescope

load(ubuntu-click)

QT += qml quick dbus
CONFIG += c++11

STARFISH_PATH = ../starfish

SOURCES += \
    $$STARFISH_PATH/servicecontrol.cpp \
    $$STARFISH_PATH/watch.cpp \
    $$STARFISH_PATH/watches.cpp \
    main.cpp

HEADERS += \
    $$STARFISH_PATH/servicecontrol.h \
    $$STARFISH_PATH/watch.h \
    $$STARFISH_PATH/watches.h \

RESOURCES += telescope.qrc

OTHER_FILES += telescope.apparmor \
               telescope.desktop \
               telescope.svg \

#specify where the config files are installed to
config_files.path = /telescope
config_files.files += $${OTHER_FILES}
message($$config_files.files)
INSTALLS+=config_files

# Default rules for deployment.
target.path = $${UBUNTU_CLICK_BINARY_PATH}
INSTALLS+=target

