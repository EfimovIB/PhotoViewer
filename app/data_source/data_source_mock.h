#pragma once

#include <memory>

#include "data_source.h"

#include "base/albums_dict.h"
#include "base/photos_dict.h"

class DataSourceMock
  : public DataSource
{
    Q_OBJECT

public:
    DataSourceMock(QObject* parent);

    std::vector<std::shared_ptr<User>> users() const override;
    std::vector<std::shared_ptr<Album>> albums(const user_id _userId) const override;
    std::vector<std::shared_ptr<Photo>> photos(const album_id _albumId) const override;

    size_t photosCount(const album_id albumId) const override;
    QString firstThumbnailUrl(const album_id albumId) const override;

private:

    void load() override;

    std::vector<std::shared_ptr<User>> m_users;
    AlbumsDict m_albums;
    PhotosDict m_photos;
};

