import QtQuick 2.12
import QtQuick.Controls 2.4

import ToolsModule 1.0

ListView {
    id: root

    signal albumIdChanged(int albumId)

    orientation: ListView.Horizontal
    model: albumModel
    delegate: AlbumCover {
        width: height
        height: root.height
        photosCount: albumModel.photosCount(id)
        previewUrl: albumModel.firstThumbnailUrl(id)
        albumName: title
        selected: root.currentIndex == index
        MouseArea {
            anchors.fill: parent
            onClicked: root.currentIndex = index
        }
    }

    onCurrentItemChanged:root.albumIdChanged(model.data(model.index(currentIndex, 0), albumModel.albumIdRole()))
    Component.onCompleted: currentIndex = 0
    Connections {
        target: albumModel
        onUserIdChanged: root.currentIndex = 0
    }
}
