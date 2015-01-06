import QtQuick 2.2
import QtQuick.Controls 1.1

Item {
    id: busScheduleView
    objectName: "busScheduleView"
    width: parent.width
    height: parent.height

    property int id

    Label {
        id: busIdLabel
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        text: "Bus ID: " + id
    }

    ListModel {
        id: scheduleModel
    }

    ScrollView {
        anchors.top: busIdLabel.bottom
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
            delegate: Item {
                height: Math.max(label1.height, label2.height) + 4
                width: parent.width

                Label {
                    id: label1
                    text: stopName
                    anchors.top: parent.top
                    anchors.topMargin: 8
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                }

                Label {
                    id: label2
                    text: time
                    horizontalAlignment: Text.AlignRight
                    anchors.top: parent.top
                    anchors.topMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                }
            }
        }
    }

    function addItem(stopName, time) {
        scheduleModel.append({"stopName": stopName, "time": time});
    }
}
