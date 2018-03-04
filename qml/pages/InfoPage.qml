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

Page {

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: contentColumn.height + Theme.paddingSmall
        anchors.margins: Theme.paddingLarge

        Column {
            id: contentColumn
            width: parent.width
            height: childrenRect.height
            spacing: Theme.paddingLarge

            PageHeader {
                title: "About Starfish"
            }

            Row {
                width: parent.width
                spacing: Theme.paddingLarge
                anchors.margins: Theme.paddingLarge

                Image {
                    source: "qrc:///starfish.png"
                    height: Theme.iconSizeLarge
                    width: height
                }

                Label {
                    text: qsTr("Version %1").arg(version)
                    font.pixelSize: Theme.fontSizeLarge
                }
            }

            Separator {
                width: parent.width
                color: Theme.secondaryHighlightColor
            }

            Label {
                width: parent.width
                text: qsTr("Legal")
                font.bold: true
            }

            Label {
                width: parent.width
                font.pixelSize: Theme.fontSizeSmall
                text: "This program is free software: you can redistribute it and/or modify "
                      + "it under the terms of the GNU General Public License as published "
                      + "by the Free Software Foundation, version 3 of the License.<br>"
                      + "This program is distributed in the hope that it will be useful, "
                      + "but WITHOUT ANY WARRANTY; without even the implied warranty of "
                      + "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
                      + "GNU General Public License for more details.<br>"
                      + "You should have received a copy of the GNU General Public License "
                      + "along with this program.  If not, see <a href=\"http://www.gnu.org/"
                      + "licenses/\">http://www.gnu.org/licenses</a>."
                wrapMode: Text.WordWrap
            }
        }
    }
}

