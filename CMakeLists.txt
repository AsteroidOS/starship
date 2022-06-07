cmake_minimum_required(VERSION 3.15)
project(harbour-starship VERSION 1.0.0 LANGUAGES CXX)

find_package (Qt5 COMPONENTS Core Network Qml Gui Quick REQUIRED)

include(FindPkgConfig)
pkg_search_module(SAILFISH sailfishapp REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SAILFISHOS_PLATFORM  ON)

add_subdirectory(asteroidsyncservice)

add_executable(harbour-starship src/harbour-starship.cpp)

target_compile_definitions(harbour-starship PRIVATE
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
    SAILFISHOS_PLATFORM
)

target_compile_definitions(asteroidsyncserviced PUBLIC
    SAILFISHOS_PLATFORM
)

target_compile_options(harbour-starship PRIVATE -Wall -Wextra -Wpedantic)

target_compile_features(harbour-starship PUBLIC cxx_std_17)

target_include_directories(harbour-starship PRIVATE
    $<BUILD_INTERFACE:
    ${SAILFISH_INCLUDE_DIRS}>
)


target_link_libraries(harbour-starship
    Qt5::Quick
    ${SAILFISH_LDFLAGS}
)

configure_file(
    "harbour-starship_config.h.in"
    "harbour-starship_config.h"
)

install(TARGETS harbour-starship
    RUNTIME DESTINATION bin
)
install(DIRECTORY qml
    DESTINATION share/harbour-starship
)
install(DIRECTORY translations
    DESTINATION share/harbour-starship
    FILES_MATCHING PATTERN "*.qm"
)
install(FILES harbour-starship.desktop
    DESTINATION share/applications
)
install(FILES icons/86x86/harbour-starship.png
    DESTINATION share/icons/hicolor/86x86/apps
)
install(FILES icons/108x108/harbour-starship.png
    DESTINATION share/icons/hicolor/108x108/apps
)
install(FILES icons/128x128/harbour-starship.png
    DESTINATION share/icons/hicolor/128x128/apps
)
install(FILES icons/172x172/harbour-starship.png
    DESTINATION share/icons/hicolor/172x172/apps
)

# Get the other files reachable from the project tree in Qt Creator
FILE(GLOB TsFiles "translations/*.ts")
add_custom_target(distfiles
    SOURCES
        harbour-starship.desktop
        qml/harbour-starship.qml
        qml/cover/CoverPage.qml
        qml/pages/InfoPage.qml
        qml/pages/LoadingPage.qml
        qml/pages/MainMenuPage.qml
        qml/pages/WatchSelectionPage.qml
        qml/pullDownMenus/StarshipPullDownMenu.qml
        qml/img/harbour-starship.svg
        rpm/harbour-starship.changes.in
        rpm/harbour-starship.changes.run.in
        rpm/harbour-starship.spec
        rpm/harbour-starship.yaml
        ${TsFiles})

# Tell Qt Creator where the application executable(s) would be located on the
# device.
#
# It is not necessary to list other deployables than executables (runtime
# targets) here. The deployment process of Sailfish OS projects is opaque to
# Qt Creator and the information contained in QtCreatorDeployment.txt is only
# used to locate the executable associated with the active run configuration
# on the device in order to run it.
#
# Search the Qt Creator Manual to learn about the QtCreatorDeployment.txt file
# format.
file(WRITE "${CMAKE_BINARY_DIR}/QtCreatorDeployment.txt"
    "${CMAKE_INSTALL_PREFIX}
${CMAKE_BINARY_DIR}/harbour-starship:bin
")

