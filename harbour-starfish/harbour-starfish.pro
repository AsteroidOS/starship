# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-starfish

CONFIG += sailfishapp
CONFIG += starfish
include(../version.pri)

SOURCES += src/harbour-starfish.cpp

DISTFILES += qml/harbour-starfish.qml \
    qml/cover/CoverPage.qml \
    qml/pages/InfoPage.qml \
    qml/pages/LoadingPage.qml \
    qml/pages/LocationPicker.qml \
    qml/pages/MainMenuPage.qml \
    qml/pages/WatchSelectionPage.qml \
    qml/pages/WeatherSettingsDialog.qml \
    qml/pullDownMenus/StarfishPullDownMenu \
    translations/*.ts \
    harbour-starfish.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-starfish-de.ts
