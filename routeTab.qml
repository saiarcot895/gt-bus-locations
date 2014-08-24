import QtQuick 2.2
import QtQuick.Controls 1.1

Tab {
    asynchronous: true
    anchors.fill: parent

    property var myModel

    ListView {
        id: directionsList
        objectName: "directionsList"
        orientation: ListView.Vertical
        anchors.fill: parent
        delegate: Button { text: name }
        model: myModel
    }
}
