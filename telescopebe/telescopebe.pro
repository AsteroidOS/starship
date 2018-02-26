TEMPLATE = lib
TARGET = Telescopebackend
QT += qml quick dbus
CONFIG += qt plugin
CONFIG += c++11

load(ubuntu-click)

TARGET = $$qtLibraryTarget($$TARGET)

STARFISH_PATH = ../starfish

# Input
SOURCES += \
    $$STARFISH_PATH/servicecontrol.cpp \
    $$STARFISH_PATH/watch.cpp \
    $$STARFISH_PATH/watches.cpp \
    backend.cpp \
    mytype.cpp

HEADERS += \
    $$STARFISH_PATH/servicecontrol.h \
    $$STARFISH_PATH/watch.h \
    $$STARFISH_PATH/watches.h \
    backend.h \
    mytype.h

OTHER_FILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
installPath = $${UBUNTU_CLICK_PLUGIN_PATH}/Telescope
qmldir.path = $$installPath
target.path = $$installPath
INSTALLS += target qmldir

