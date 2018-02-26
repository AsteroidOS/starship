TEMPLATE = subdirs

#CONFIG += utouch

SUBDIRS = starfishd starfishd

OTHER_FILES = telescope.pri

utouch {
    include(telescope.pri)
    SUBDIRS -= starfishd starfishd
}

OTHER_FILES += \
    README.md \
    rpm/starfish.spec
