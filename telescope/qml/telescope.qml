import QtQuick 2.4
import Ubuntu.Components 1.3
import Telescope 1.0

/*!
    \brief MainView with a Label and Button elements.
*/

MainView {

    property alias curWatch: watches.currentWatch
    property alias curWatchConnected: watches.currentWatchConnected
    property var sysProfiles: [ ]

    // Note! applicationName needs to match the "name" field of the click manifest
    applicationName: "telescope.asteroidos"
    automaticOrientation: true
    anchorToKeyboard: true
    width: units.gu(45)
    height: units.gu(75)

    ServiceController {
        id: serviceController
        serviceName: "telescoped"
        Component.onCompleted: {
            if (!serviceController.serviceFileInstalled) {
                print("Service file not installed. Installing now.")
                serviceController.installServiceFile();
            }
            if (!serviceController.serviceRunning) {
                print("Service not running. Starting now.")
                serviceController.startService();
            }
        }
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
                pageStack.push("qrc:/qml/pages/MainMenuPage.qml", {watch: getCurWatch()})
            else
                pageStack.push("qrc:/qml/pages/WatchesPage.qml");
        } else {
            pageStack.clear();
            pageStack.push("qrc:/qml/pages/LoadingPage.qml");
        }
    }

    Component.onCompleted: loadStack();

    function getCurWatch() {
        if(curWatch >= 0) return watches.get(curWatch);
        return null;
    }

    PageStack {
        id: pageStack
    }
}


