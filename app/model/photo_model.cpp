#include "photo_model.h"

#include "data_source/data_source.h"
#include "base/photo.h"

PhotoModel::PhotoModel(DataSource* dataSource, QObject* parent)
  : QAbstractListModel(parent)
  , m_dataSource(dataSource)
{
    connect(m_dataSource, &DataSource::dataUpdated, this, &PhotoModel::resetModel);
}

int PhotoModel::albumId() const
{
    return m_albumId;
}

void PhotoModel::setAlbumId(int _albumId)
{
    m_albumId = _albumId;
    resetModel();
    emit albumIdChanged();
}

int PhotoModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(m_photos.size());
}

QVariant PhotoModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return {};

    const std::shared_ptr<Photo>& photo = m_photos[static_cast<size_t>(index.row())];

    switch (role)
    {
    case P_Id: return static_cast<int>(photo->id);
    case P_AlbumId: return static_cast<int>(photo->albumId);
    case P_Title: return photo->title;
    case P_Url: return photo->url;
    case P_ThumbnailUrl: return photo->thumbnailUrl;
    }

    return {};
}

void PhotoModel::resetModel()
{
    beginResetModel();
    m_photos = m_dataSource->photos(m_albumId);
    endResetModel();
}
