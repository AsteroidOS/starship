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
import Sailfish.Silica 1.0
import "../pullDownMenus"

Page {
    SilicaListView {
        anchors.fill: parent
        model: watches

        StarshipPullDownMenu {}

        header: PageHeader {
            title: qsTr("Starship")
            description: qsTr("Manage Watches")
        }

        delegate: ListItem {
            enabled: watches.count !== 0
            width: parent.width

            RowLayout {
                    height: Theme.iconSizeLarge
                    width: parent.width

                Icon {
                    height: Theme.iconSizeSmall
                    width: height
                    source: "image://theme/icon-m-watch"
                }

                ColumnLayout {
                    Label {
                        text: name
                    }

                    Label {
                        text: address
                    }
                }
            }

            onClicked: watches.selectWatch(index)
        }

        ViewPlaceholder {
            enabled: watches.count === 0

            Label {
                id: noWatchLabel
                text: qsTr("No smartwatches configured yet. Please connect your smartwatch using System Settings.")
                font.pixelSize: Theme.fontSizeLarge
                width: parent.width-(Theme.paddingSmall*2)
                anchors.centerIn: parent
                anchors.bottomMargin: Theme.paddingLarge
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
            }

            Button {
                text: qsTr("Open Bluetooth Settings")
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: Theme.paddingLarge
                anchors.top: noWatchLabel.bottom
                onClicked: starship.startBT()
            }
        }
    }
}
