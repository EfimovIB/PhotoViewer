import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import ViewModule 1.0
import ToolsModule 1.0

Window {
    id: root
    visible: true
    width: 900
    height: 480
    title: qsTr("Photo Viewer")

    ColumnLayout {
        anchors.fill: parent

        ComboBox {
            id: _userCombobox
            Layout.fillWidth: true
            model: userModel
            textRole: "userName"
            displayText: "user: " + currentText
            onCurrentIndexChanged: albumModel.userId = model.data(model.index(currentIndex, 0), userModel.userIdRole())
        }

        AlbumsView {
            id: _albumView
            Layout.preferredHeight: 150
            Layout.fillWidth: true
            onAlbumIdChanged: photoModel.albumId = albumId
        }

        PhotosView {
            id: _photosView
            Layout.fillWidth: true
            Layout.fillHeight: true
            cellHeight: 100
            cellWidth: 100
            onPhotoIndexChanged: {
                _bigPicture.url = photoModel.data(photoModel.index(photoIndex, 0), photoModel.urlRole())
                _bigPicture.title = photoModel.data(photoModel.index(photoIndex, 0), photoModel.titleRole())
            }
        }
    }

    BigPicture {
        id: _bigPicture
        anchors.fill: parent
        z: 2
    }

}
