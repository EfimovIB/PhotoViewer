#pragma once

#include <QAbstractListModel>

#include "base/types.h"

class DataSource;
struct Photo;

class PhotoModel
  : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int albumId READ albumId WRITE setAlbumId NOTIFY albumIdChanged)

public:

    PhotoModel(DataSource* dataSource, QObject* parent = nullptr);

    int albumId() const;
    void setAlbumId(int _albumId);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE int urlRole() const { return P_Url; }
    Q_INVOKABLE int titleRole() const { return P_Title; }

    QHash<int, QByteArray> roleNames() const override
    {
        return {
            {P_Id, "id"}
          , {P_AlbumId, "albumId"}
          , {P_Title, "title"}
          , {P_Url, "url"}
          , {P_ThumbnailUrl, "thumbnailUrl"}
        };
    }

signals:

    void albumIdChanged();

private:

    enum PhotoModelRoles
    {
        P_Id = Qt::UserRole + 1
      , P_AlbumId
      , P_Title
      , P_Url
      , P_ThumbnailUrl
    };

    void resetModel();

    DataSource* m_dataSource;
    album_id m_albumId;
    std::vector<std::shared_ptr<Photo>> m_photos;
};
