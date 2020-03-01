import QtQuick 2.0

Item {
    id: root

    property bool selected: false
    property int photosCount: 0
    property string previewUrl: ""
    property string albumName: ""

    Rectangle {
        anchors { fill: root; margins: _preview.anchors.margins - 3 }
        color: "black"
        visible: root.selected
    }

    Image {
        id: _preview
        anchors { fill: parent; margins: 5 }
        source: root.previewUrl
        ImageNotFoundCover {}

        GlassFooter {
            id: _footer
            Text {
                id: _albumTitle
                anchors { left: _footer.left; verticalCenter: _footer.verticalCenter; right: _albumPhotosCount.left; leftMargin: 5 }
                elide: Text.ElideRight
                text: root.albumName
            }
            Text {
                id: _albumPhotosCount
                anchors { right: _footer.right; verticalCenter: _footer.verticalCenter; rightMargin: 5 }
                text: root.photosCount
            }
        }
    }
}

