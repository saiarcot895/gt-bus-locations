import QtQuick 2.1
import QtQuick.Controls 1.0

Item {

    ListView {
        anchors.fill: parent
        delegate: directionsDelegate
    }
}
