import QtQuick 2.12
import QtQuick.Controls 2.4

import ToolsModule 1.0

Item {
    id: root

    property alias cellHeight: _grid.cellHeight
    property alias cellWidth: _grid.cellWidth

    signal photoIndexChanged(int photoIndex)

    onWidthChanged: centrateGrid()

    function centrateGrid() {
        var cellCountInRow = Math.floor(root.width / _grid.cellWidth)
        var gap = root.width - cellCountInRow * _grid.cellWidth
        _grid.leftMargin = gap / 2
    }

    GridView {
        id: _grid
        anchors { left: root.left; top: root.top; right: root.right; bottom: root.bottom }
        clip: true
        model: photoModel

        delegate: Rectangle {
            width: _grid.cellHeight - 1
            height: _grid.cellWidth - 1

            Image {
                id: _image
                anchors.fill: parent
                source: thumbnailUrl
                ImageNotFoundCover {}
            }
            MouseArea {
                anchors.fill: parent
                onClicked: root.photoIndexChanged(index)
            }
        }
    }
}
