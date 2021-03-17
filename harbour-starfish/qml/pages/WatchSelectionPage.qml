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
import "../PullDownMenus"

Page {
    SilicaListView {
        anchors.fill: parent
        model: watches

        header: PageHeader {
            title: qsTr("Starfish")
            description: qsTr("Manage Watches")
        }

        pullDownMenu: StarfishPullDownMenu {}

        delegate: ListItem {
            contentHeight: Theme.fontSizeMedium*2

            Label {
                text: name
                anchors.fill: parent
            }

            onClicked: watches.selectWatch(index)
        }

        ViewPlaceholder {
            anchors.fill: parent
            enabled: watches.count === 0

            Label {
                text: qsTr("No smartwatches configured yet. Please connect your smartwatch using System Settings.")
                font.pixelSize: Theme.fontSizeLarge
                width: parent.width-(Theme.paddingSmall*2)
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
            }

            Button {
                text: qsTr("Open Bluetooth Settings")
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottomMargin: Theme.paddingLarge
                anchors.bottom: parent.bottom
                onClicked: starfish.startBT()
            }
        }
    }

}
