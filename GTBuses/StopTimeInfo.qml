import QtQuick 2.2
import QtQuick.Controls 1.1

Item {
    width: parent.width
    height: label2.height
    property string time: ""
    property string position: ""

    Label {
        id: label1
        text: time
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
    }

    Label {
        id: label2
        text: position
        horizontalAlignment: Text.AlignRight
        wrapMode: Text.Wrap
        anchors.verticalCenter: label1.verticalCenter
        anchors.left: label1.right
        anchors.leftMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
    }
}
