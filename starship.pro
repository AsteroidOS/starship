TEMPLATE = subdirs

CONFIG += sailfishapp
CONFIG += starship

SUBDIRS = harbour-starship asteroidsyncservice

include(version.pri)

DISTFILES += \
    rpm/harbour-starship.changes.in \
    rpm/harbour-starship.changes.run.in \
    rpm/harbour-starship.spec \
    rpm/harbour-starship.yaml \
