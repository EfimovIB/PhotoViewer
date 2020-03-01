#pragma once

#include <QAbstractListModel>

#include "base/types.h"

class DataSource;
struct Album;

class AlbumModel
  : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int userId READ userId WRITE setUserId NOTIFY userIdChanged)

public:

    AlbumModel(DataSource* dataSource, QObject* parent = nullptr);

    int userId() const;
    void setUserId(int _userId);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE int albumIdRole() const { return A_Id; }

    Q_INVOKABLE int photosCount(int albumId) const;
    Q_INVOKABLE QString firstThumbnailUrl(int albumId) const;

    QHash<int, QByteArray> roleNames() const override
    {
        return {
            {A_Id, "id"}
          , {A_Title, "title"}
          , {A_UserId, "userId"}
        };
    }

signals:

    void userIdChanged();

private:

    enum AlbumModelRoles
    {
        A_Id = Qt::UserRole + 1
      , A_Title
      , A_UserId
    };

    void resetModel();

    DataSource* m_dataSource;
    user_id m_userId;
    std::vector<std::shared_ptr<Album>> m_albums;
};
