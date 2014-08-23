import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.1

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
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    TabView {
        anchors.fill: parent

        Tab {
            id: tab1
            source: "directionsTab.qml"
            asynchronous: true
            visible: status == Loader.Ready
            title: "Tab"
        }

    }

    Component {
        id: directionsDelegate
        Item {
            Column {
                Text { text: name }
            }
        }
    }

    Component {
        id: stopsDelegate
        Item {
            Column {
                Text { text: name }
            }
        }
    }
}
