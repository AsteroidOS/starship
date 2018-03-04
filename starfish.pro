TARGET = starfish

include(version.pri)

QT += qml quick dbus

CONFIG += c++11
CONFIG += sailfishapp

SOURCES += main.cpp

RESOURCES += starfish.qrc

QML_FILES += $$files(qml/*.qml,true)
QML_FILES += $$files(qml/pages/*.qml,true)
QML_FILES += $$files(qml/cover/*.qml,true)

CONF_FILES +=  starfish.png \
               starfish.desktop \
               $$files(translations/*.ts,true)

OTHER_FILES += $${QML_FILES} \
               $${CONF_FILES} \
               README.md \
               rpm/starfish.spec

qml.path = /usr/share/starfish/qml
qml.files += $${QML_FILES}

target.path = /usr/bin

lupdate_only { SOURCES += QML_FILES }

CONFIG += sailfishapp_i18n
TRANSLATIONS += $$files(translations/*.ts, true)
