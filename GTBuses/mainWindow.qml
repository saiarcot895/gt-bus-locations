import QtQuick 2.2
import QtQuick.Controls 1.1

Item {
    id: mainWindowItem
    objectName: "mainWindowItem"
    anchors.fill: parent

    property var routesModel: null
    property var directionsModel: null
    property var stopsModel: null

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
        enabled: routesModel
        anchors.left: label1.right
        anchors.leftMargin: 6
        anchors.top: parent.top
        anchors.topMargin: 8
        model: routesModel
        textRole: "name"
        onCurrentTextChanged: {
            mainWindow.displayDirections(currentIndex);
            mainWindow.displayStops(0);
        }
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
        enabled: routesModel
        anchors.top: comboBox1.bottom
        anchors.topMargin: 6
        anchors.left: label2.right
        anchors.leftMargin: 6
        model: directionsModel
        textRole: "name"
        onCurrentTextChanged: mainWindow.displayStops(currentIndex)
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
        objectName: "stopsComboBox"
        enabled: routesModel
        anchors.top: comboBox2.bottom
        anchors.topMargin: 6
        anchors.left: label3.right
        anchors.leftMargin: 6
        model: stopsModel
        textRole: "name"
        onCurrentTextChanged: mainWindow.displayStopTimes(currentIndex)
    }

    Button {
        id: button1
        visible: false
        text: qsTr("Map")
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
    }

    Rectangle {
        id: rectangle1
        objectName: "stopTimesRectangle"
        color: "#00000000"
        visible: false
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8

        StopTimeInfo {
            id: stopTime0
            objectName: "stopTime0"
            anchors.top: parent.top
            anchors.topMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.right: parent.right
            anchors.rightMargin: 8
        }

        StopTimeInfo {
            id: stopTime1
            objectName: "stopTime1"
            anchors.top: stopTime0.bottom
            anchors.topMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.right: parent.right
            anchors.rightMargin: 8
        }

        StopTimeInfo {
            id: stopTime2
            objectName: "stopTime2"
            anchors.top: stopTime1.bottom
            anchors.topMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.right: parent.right
            anchors.rightMargin: 8
        }
    }
}
