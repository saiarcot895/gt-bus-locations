import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("GT Buses")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")

            MenuItem {
                text: qsTr("About")
                onTriggered: mainController.showAboutScreen();
            }

            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    MainWindow {
        id: mainWindowItem
        objectName: "mainWindowItem"
        anchors.fill: parent
        visible: loader.source == ""
    }

    Loader {
        id: loader
        objectName: "loader"
        anchors.fill: parent
    }
}
