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

    Component {
        id: stopsDelegate
        Item {
            Column {
                Text { text: name }
            }
        }
    }

    Label {
        id: label1
        text: qsTr("Route")
        anchors.leftMargin: 8
        anchors.verticalCenter: comboBox1.verticalCenter
        anchors.left: parent.left
    }

    ComboBox {
        id: comboBox1
        objectName: "routesComboBox"
        enabled: false
        anchors.left: label1.right
        anchors.leftMargin: 6
        anchors.top: parent.top
        anchors.topMargin: 8
        model: routesModel
        textRole: "name"
        onCurrentTextChanged: mainWindow.displayDirections(currentIndex)
    }

    Label {
        id: label2
        text: qsTr("Direction")
        anchors.verticalCenter: comboBox2.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 8
    }

    ComboBox {
        id: comboBox2
        objectName: "directionsComboBox"
        enabled: false
        anchors.top: comboBox1.bottom
        anchors.topMargin: 6
        anchors.left: label2.right
        anchors.leftMargin: 6
        model: directionsModel
        textRole: "name"
    }

    Label {
        id: label3
        text: qsTr("Stop")
        anchors.verticalCenter: comboBox3.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 8
    }

    ComboBox {
        id: comboBox3
        enabled: false
        anchors.top: comboBox2.bottom
        anchors.topMargin: 6
        anchors.left: label3.right
        anchors.leftMargin: 6
        model: stopsModel
    }
}
