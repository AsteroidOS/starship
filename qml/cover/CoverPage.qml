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

CoverBackground {
    property var watch: null

    Image {
        fillMode: Image.PreserveAspectCrop
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: label.top
        source: "image://theme/icon-m-watch"
    }

    Label {
        id: label
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: state.top
        anchors.bottomMargin: Theme.paddingSmall
        text: (watch && watch.name) ? watch.name : qsTr("Watch")
    }

    Label {
        id: state
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.verticalCenter
        color: Theme.highlightColor
        text: (curWatchConnected) ? qsTr("connected") : qsTr("disconnected")
    }

    onStatusChanged: {
        if (status===Cover.Activating) {
            watch = starship.getCurWatch()
        }
    }
}
