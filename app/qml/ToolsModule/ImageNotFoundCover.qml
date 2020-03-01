import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    visible: parent.source == ""
    color: "white"
    border.color: "black"
    border.width: 1
    Text {
        anchors.centerIn: parent
        text: qsTr("No image")
    }
}
