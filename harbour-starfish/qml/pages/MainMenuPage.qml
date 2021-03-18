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
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0

import Sailfish.Silica 1.0
import "../pullDownMenus"

Page {
    id: pageRoot
    property var curWatch: null
    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent

        StarfishPullDownMenu {}

        Column {
            id: column
            spacing: Theme.paddingLarge
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: Theme.paddingMedium

            PageHeader {
                title: pageRoot.curWatch ? pageRoot.curWatch.name : qsTr("Watch")
                description: qsTr("Menu")
            }

            RowLayout {
                width: parent.width
                height: Theme.iconSizeLarge

                RowLayout {
                    height: Theme.iconSizeLarge

                    Icon {
                        height: Theme.iconSizeSmall
                        width: height
                        source: "image://theme/icon-m-" + (curWatchConnected ? "bluetooth-device" : "warning")
                        Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
                    }

                    Label {
                        padding: Theme.paddingLarge
                        color: Theme.highlightColor
                        font.pixelSize: Theme.fontSizeMedium
                        text: curWatchConnected ? qsTr("Connected") : qsTr("Disconnected")
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignCenter
                    }
                }

                RowLayout {
                    height: Theme.iconSizeLarge

                    Icon {
                        height: Theme.iconSizeSmall
                        width: height
                        source: "image://theme/icon-m-charging"
                        Layout.alignment: Qt.AlignCenter
                    }

                    Label {
                        padding: Theme.paddingLarge
                        color: Theme.highlightColor
                        font.pixelSize: Theme.fontSizeMedium
                        text: curWatchConnected ? pageRoot.curWatch.batteryLevel + ("%") : qsTr("unknown")
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignCenter
                    }

                }
            }

        }
    }
}
