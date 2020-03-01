import QtQuick 2.0

Rectangle {
    id: root
    anchors { left: parent.left; bottom: parent.bottom; right: parent.right }
    height: Math.min(20, parent.height / 5)
    color: "lightgrey"
    opacity: 0.4
}
