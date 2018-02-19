/*
 * Copyright (C) 2018 - Florent Revest <revestflo@gmail.com>
 *               2016 - Andrew Branson <andrew.branson@jollamobile.com>
 *                      Ruslan N. Marchenko <me@ruff.mobi>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.2
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0

Page {
    id: root
    property var watch: null
    allowedOrientations: Orientation.All

    ListModel {
        id: mainMenuModel
        dynamicRoles: true
    }

    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("InfoPage.qml"))
            }
            MenuItem {
                text: qsTr("Restart service")
                onClicked: starfish.restartService()
            }
        }

        Column {
            anchors.fill: parent
            spacing: Theme.paddingMedium

            PageHeader {
                id: hdr
                title: root.watch ? root.watch.name : ""
            }

            Row {
                height: Theme.iconSizeSmall
                spacing: Theme.paddingSmall

                Image {
                    height: Theme.iconSizeSmall
                    width: height
                    source: "image://theme/icon-lock-" + (curWatchConnected ? "transfer" : "warning")
                }

                Label {
                    text: curWatchConnected ? qsTr("Connected") : qsTr("Disconnected")
                }
            }

            Label {
                text: qsTr("Your smartwatch is disconnected. Please make sure it is powered on, within range and it is paired properly in the Bluetooth System Settings.")
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                wrapMode: Text.WordWrap
                visible: !curWatchConnected
                font.pixelSize: Theme.fontSizeLarge
                horizontalAlignment: Text.AlignHCenter
            }

            Button {
                text: qsTr("Open Bluetooth Settings")
                visible: curWatchConnected
                onClicked: starfish.startBT()
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Repeater {
                id: menuRepeater
                model: curWatchConnected ? mainMenuModel : null
                delegate: ListItem {
                    contentHeight: Theme.iconSizeMedium + Theme.paddingSmall*2
                    Row {
                        height: Theme.iconSizeMedium
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: Theme.paddingSmall
                        Image {
                            source: "image://theme/" + model.icon
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Label {
                            text: model.text
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                    onClicked: {
                        var options = {}
                        options["watch"] = root.watch
                        pageStack.push(Qt.resolvedUrl(model.page), options)
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        mainMenuModel.clear()
        mainMenuModel.append({
                                 icon: "icon-m-alarm",
                                 text: qsTr("Weather"),
                                 page: "WeatherSettingsDialog.qml"
                             })
    }
}

