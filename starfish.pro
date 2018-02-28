TEMPLATE = subdirs

#CONFIG += utouch

SUBDIRS = starfish starfishd

OTHER_FILES = telescope.pri

utouch {
    include(telescope.pri)
    SUBDIRS -= starfish
}

OTHER_FILES += \
    README.md \
    rpm/starfish.spec
