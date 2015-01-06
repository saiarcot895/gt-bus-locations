import QtQuick 2.2
import QtQuick.Controls 1.1

Item {
    implicitWidth: parent.width
    implicitHeight: Math.max(label1.height, label2.height, fullScheduleButton.height) + 8
    property string time
    property string position
    property int busId

    Label {
        id: label1
        text: time
        anchors.verticalCenter: fullScheduleButton.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 8
    }

    Button {
        id: fullScheduleButton
        anchors.top: parent.top
        anchors.left: label1.right
        anchors.leftMargin: 6
        text: "Show bus schedule"
        onClicked: mainWindow.displayBusSchedule(busId)
    }

    Label {
        id: label2
        text: position
        horizontalAlignment: Text.AlignRight
        wrapMode: Text.Wrap
        visible: parent.width > label1.width + fullScheduleButton.width + 22 + 75
        height: visible ? implicitHeight : 0
        anchors.verticalCenter: fullScheduleButton.verticalCenter
        anchors.left: fullScheduleButton.right
        anchors.leftMargin: 6
        anchors.right: parent.right
        anchors.rightMargin: 8
    }
}
