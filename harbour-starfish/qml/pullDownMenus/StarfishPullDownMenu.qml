import QtQuick 2.2
import Sailfish.Silica 1.0

PullDownMenu {
    MenuItem {
        text: qsTr("About")
        onClicked: pageStack.push(Qt.resolvedUrl("../pages/InfoPage.qml"))
    }
    MenuItem {
        text: qsTr("Bluetooth Settings")
        onClicked: starfish.startBT()
    }
    MenuItem {
        text: qsTr("Restart service")
        onClicked: starfish.restartService()
    }
}
