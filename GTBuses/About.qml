import QtQuick 2.2
import QtQuick.Controls 1.1

Item {
    id: aboutView

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
        id: authorNameLabel
        font.pointSize: 17
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: backButton.bottom
        anchors.topMargin: 6
        text: "Created by Saikrishna Arcot"
    }

    Label {
        id: iconCreditsLabel
        font.pointSize: 12
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: authorNameLabel.bottom
        anchors.topMargin: 6
        text: "Icon by Sascha Elmers, released under CC-BY 3.0"
    }
}
