#include "album_model.h"

#include "data_source/data_source.h"
#include "base/album.h"

AlbumModel::AlbumModel(DataSource* dataSource, QObject* parent)
  : QAbstractListModel(parent)
  , m_dataSource(dataSource)
{
    connect(m_dataSource, &DataSource::dataUpdated, this, &AlbumModel::resetModel);
}

int AlbumModel::userId() const
{
    return m_userId;
}

void AlbumModel::setUserId(int _userId)
{
    m_userId = _userId;
    resetModel();
    emit userIdChanged();
}

int AlbumModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(m_albums.size());
}

QVariant AlbumModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return {};

    const std::shared_ptr<Album>& album = m_albums[static_cast<size_t>(index.row())];

    switch (role)
    {
    case A_Id: return static_cast<int>(album->id);
    case A_UserId: return static_cast<int>(album->userId);
    case A_Title: return album->title;
    }

    return {};
}

int AlbumModel::photosCount(int albumId) const
{
    return m_dataSource->photosCount(albumId);
}

QString AlbumModel::firstThumbnailUrl(int albumId) const
{
    return m_dataSource->firstThumbnailUrl(albumId);
}

void AlbumModel::resetModel()
{
    beginResetModel();
    m_albums = m_dataSource->albums(m_userId);
    endResetModel();
}
