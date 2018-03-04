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
import org.asteroid.syncservice 1.0
import org.nemomobile.dbus 2.0
import "pages"

ApplicationWindow {
    id: starfish
    initialPage: Qt.resolvedUrl("pages/LoadingPage.qml")
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    property alias curWatch: watches.currentWatch
    property alias curWatchConnected: watches.currentWatchConnected
    property var sysProfiles: [ ]

    ServiceController {
        id: serviceController
        Component.onCompleted: initService()
    }

    Watches {
        id: watches
        onCountChanged: loadStack()
        onConnectedToServiceChanged: loadStack()
        onCurrentWatchChanged: {
            console.log("onCurrentWatchChanged" + curWatch)
            loadStack()
        }
    }

    DBusInterface {
        id: lipstick
        service: "org.nemomobile.lipstick"
        path: "/LauncherModel"
        iface: "org.nemomobile.lipstick.LauncherModel"
    }

    DBusInterface {
        id: jolla
        service: "com.jolla.settings"
        path: "/com/jolla/settings/ui"
        iface: "com.jolla.settings.ui"
    }

    function startBT() {
        lipstick.typedCall("notifyLaunching",[{"type":"s","value":"jolla-settings.desktop"}],
                           function(r){jolla.call("showPage",["system_settings/connectivity/bluetooth"])},
                           function(e){console.log("Error",e)})
    }

    function initService() {
        if (!watches.connectedToService && !serviceController.serviceRunning) {
            serviceController.startService();
        }
        if (watches.version !== version) {
            console.log("Service file version (", version, ") is not equal running service version (", watches.version, "). Restarting service.");
            serviceController.restartService();
        }
    }

    function restartService() {
        serviceController.restartService()
    }

    function loadStack() {
        if (watches.connectedToService) {
            pageStack.clear()
            if (curWatch >= 0)
                pageStack.push(Qt.resolvedUrl("pages/MainMenuPage.qml"), {watch: getCurWatch()})
            else
                pageStack.push(Qt.resolvedUrl("pages/WatchesPage.qml"))
        } else {
            pageStack.clear();
            pageStack.push(initialPage);
        }
    }

    Component.onCompleted: loadStack();

    function getCurWatch() {
        if(curWatch >= 0) return watches.get(curWatch);
        return null;
    }
}

