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

Dialog {
    id: root

    property var watch: null
    canAccept: false

    SilicaFlickable {
        id: view
        anchors.fill: parent
        contentHeight: content.height
        Column {
            id:content
            width: parent.width

            DialogHeader {
                title: qsTr("Weather Settings")
                defaultAcceptText: qsTr("OK")
                defaultCancelText: qsTr("Cancel")
            }

            SectionHeader {
                text: qsTr("Locations")
            }

            ListModel {
                id: locations
            }

            SilicaListView {
                id: locList
                width: parent.width
                height: contentItem.childrenRect.height
                model: locations
                delegate: ListItem {
                    id: liLoc
                    width: locList.width - Theme.paddingSmall
                    contentHeight: contentItem.height
                    anchors.horizontalCenter: parent.horizontalCenter
                    highlighted: down || menuOpen || !enabled
                    Column {
                        id: contentItem
                        width: parent.width
                        TextField {
                            id: leName
                            width: parent.width
                            label: qsTr("Location Name")
                            text: model.name
                            visible: !liLoc.enabled
                        }
                        TextField {
                            id: leLat
                            width: parent.width
                            label: qsTr("Latitude")
                            text: model.lat
                            visible: !liLoc.enabled
                        }
                        TextField {
                            id: leLng
                            width: parent.width
                            label: qsTr("Longitude")
                            text: model.lng
                            visible: !liLoc.enabled
                        }
                        Row {
                            width: parent.width
                            spacing: Theme.paddingSmall
                            Button {
                                text: qsTr("Cancel")
                                onClicked: liLoc.enabled = true
                                visible: !liLoc.enabled
                                width: parent.width/2 - Theme.paddingSmall
                            }
                            Button {
                                text: qsTr("Save Changes")
                                width: parent.width/2 - Theme.paddingSmall
                                visible: !liLoc.enabled
                                onClicked: {
                                    locations.setProperty(index,"name",leName.text);
                                    locations.setProperty(index,"lat",leLat.text);
                                    locations.setProperty(index,"lng",leLng.text);
                                    liLoc.enabled = true;
                                }
                            }
                        }
                        Row {
                            width: parent.width
                            height: Theme.itemSizeSmall
                            visible: liLoc.enabled
                            Label {
                                width: parent.width*0.75
                                anchors.verticalCenter: parent.verticalCenter
                                text: model.name
                            }
                            Column {
                                width: parent.width/4
                                anchors.verticalCenter: parent.verticalCenter
                                Row {
                                    Label {
                                        text: "LAT: "
                                        font.pixelSize: Theme.fontSizeTiny
                                        horizontalAlignment: Text.AlignRight
                                    }
                                    Label {
                                        text: model.lat
                                        font.pixelSize: Theme.fontSizeTiny
                                    }
                                }
                                Row {
                                    Label {
                                        text: "LON: "
                                        font.pixelSize: Theme.fontSizeTiny
                                        horizontalAlignment: Text.AlignRight
                                    }
                                    Label {
                                        text: model.lng
                                        font.pixelSize: Theme.fontSizeTiny
                                    }
                                }
                            }
                        }
                    }
                    menu: ContextMenu {
                        MenuItem {
                            text: qsTr("Edit")
                            visible: index>0
                            onClicked: liLoc.enabled = false
                        }
                        MenuItem {
                            text: qsTr("Move Up")
                            visible: index>1
                            onClicked: {locations.move(index,index-1,1);root.canAccept=true}
                        }
                        MenuItem {
                            text: qsTr("Move Down")
                            visible: index>0 && index<(locations.count-1)
                            onClicked: {locations.move(index,index+1,1);root.canAccept=true}
                        }
                        MenuItem {
                            text: qsTr("Delete")
                            visible: index>0 || locations.count==1
                            onClicked: liLoc.remorseAction("Delete?",function(){locations.remove(index);root.canAccept=true})
                        }
                    }
                }
            }
            Button {
                width: parent.width
                text: qsTr("Add Location")
                onClicked: {
                    if(locations.count>0) {
                        var locpick = pageStack.push(Qt.resolvedUrl("LocationPicker.qml"));
                        locpick.accepted.connect(function(){
                            locations.append(locpick.selected);
                            root.canAccept=true;
                        });
                    } else {
                        locations.append({"name":qsTr("Current Location"),"lat":"n/a","lng":"n/a"})
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        var list = watch.weatherLocations;
        locations.clear();
        locStash = [];
        for(var i in list) {
            var loc = list[i];
            locStash.push(loc);
            locations.append({"name":loc[0],"lat":loc[1],"lng":loc[2]});
            console.log("Location",i,loc);
        }
    }

    onDone: {
        if(result === DialogResult.Accepted) {
            var ret = [];
            var locStore = false;
            for(var i=0;i<locations.count;i++) {
                var loc = locations.get(i);
                ret[i] = [loc.name,loc.lat,loc.lng];
                if(!locStore &&	(
                        locStash.length<=i ||
                        ret[i][0] !== locStash[i][0] ||
                        ret[i][1] !== locStash[i][1] ||
                        ret[i][2] !== locStash[i][2])
                    ) {
                    locStore = true;
                    console.log("Diff spotted",i,loc.name,loc.lat,loc.lng);
                }
            }

            if(locStore) {
                watch.weatherLocations = ret;
            }
        }
    }
}
