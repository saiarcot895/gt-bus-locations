import QtQuick 2.2
import QtQuick.Controls 1.1

Tab {
    asynchronous: true
    anchors.fill: parent

    property var myModel

    ListView {
        id: directionsList
        orientation: ListView.Vertical
        anchors.fill: parent
        delegate: Button {
            text: name
            objectName: model.tag
            onClicked: mainWindow.displayStops(directionsList.parent.objectName, objectName)
        }
        model: myModel
    }
}
