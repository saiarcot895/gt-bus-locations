import QtQuick 2.2
import QtQuick.Controls 1.1

Item {
    id: busScheduleView
    width: parent.width
    height: parent.height

    property int id
    property string status

    Button {
        id: backButton
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        text: "Back"
        onClicked: mainController.showMainWindow()
    }

    Label {
        id: busIdLabel
        anchors.top: backButton.bottom
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 8
        text: "Bus ID: " + id
    }

    Label {
        id: statusLabel
        anchors.top: busIdLabel.bottom
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 8
        text: "Location: " + status
    }

    ListModel {
        id: scheduleModel
    }

    ScrollView {
        anchors.top: statusLabel.bottom
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8

        ListView {
            id: scheduleView
            anchors.fill: parent
            model: scheduleModel
            delegate: Rectangle {
                height: Math.max(label1.height, label2.height) + 4
                width: parent.width
                color: highlight ? "yellow" : "transparent"

                Label {
                    id: label1
                    text: stopName
                    anchors.top: parent.top
                    anchors.topMargin: 4
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                }

                Label {
                    id: label2
                    text: time
                    horizontalAlignment: Text.AlignRight
                    anchors.top: parent.top
                    anchors.topMargin: 4
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                }
            }
        }
    }

    function addItem(stopName, time, highlight) {
        scheduleModel.append({"stopName": stopName, "time": time, "highlight": highlight});
    }
}
