TEMPLATE = aux
TARGET = telescope

RESOURCES += telescope.qrc

QML_FILES += $$files(*.qml,true) \
             $$files(*.js,true)

CONF_FILES +=  telescope.apparmor \
               icon.svg

OTHER_FILES += $${CONF_FILES} \
               $${QML_FILES} \
               telescope.desktop 

#specify where the qml/js files are installed to
qml_files.path = /telescope
qml_files.files += $${QML_FILES}

#specify where the config files are installed to
config_files.path = /telescope
config_files.files += $${CONF_FILES}

#install the desktop file, a translated version is automatically created in 
#the build directory
desktop_file.path = /telescope
desktop_file.files = $$OUT_PWD/telescope.desktop 
desktop_file.CONFIG += no_check_exist 

INSTALLS+=config_files qml_files desktop_file
