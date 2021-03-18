TEMPLATE = subdirs

CONFIG += sailfishapp
CONFIG += starfish

SUBDIRS = harbour-starfish asteroidsyncservice

include(version.pri)

DISTFILES += \
    rpm/harbour-starfish.changes.in \
    rpm/harbour-starfish.changes.run.in \
    rpm/harbour-starfish.spec \
    rpm/harbour-starfish.yaml \
