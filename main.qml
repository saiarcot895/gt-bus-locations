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
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    TabView {
        id: tabView
        objectName: "tabView"
        anchors.fill: parent
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

    function addRouteTab(routeName, tag, model) {
        var component = Qt.createComponent("routeTab.qml");
        var tab = component.createObject(tabView, {"title": routeName, "id": tag, "objectName": tag, "myModel": model});
    }
}
