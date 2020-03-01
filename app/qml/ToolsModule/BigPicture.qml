import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: root
    enabled: visible
    focus: visible
    visible: root.url !== ""

    property string url: ""
    property string title: ""

    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.8
    }

    Image {
        id: _image
        anchors { horizontalCenter: root.horizontalCenter; verticalCenter: root.verticalCenter }
        width: height
        height: Math.min(root.width, root.height)
        autoTransform: true
        fillMode: Image.PreserveAspectFit
        source: root.url
        ImageNotFoundCover {}

        GlassFooter {
            id: _footer
            Text {
                anchors { left: _footer.left; bottom: _footer.bottom; leftMargin: 5 }
                text: root.title
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        propagateComposedEvents: false
    }

    Button {
        anchors { top: root.top; right: root.right }
        text: "cancel"
        onPressed: root.url = ""
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Escape) {
            root.url = ""
        }
    }
}
