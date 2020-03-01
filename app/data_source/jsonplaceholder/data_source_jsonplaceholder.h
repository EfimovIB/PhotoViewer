#pragma once

#include <map>

#include "data_source/data_source.h"
#include "base/albums_dict.h"
#include "base/photos_dict.h"
#include "base/users_dict.h"

namespace jsph {

class Downloader;
class DataSourceJsonPlaceholder
  : public DataSource
{
    Q_OBJECT

public:

    DataSourceJsonPlaceholder(QObject* parent);

    std::vector<std::shared_ptr<User>> users() const override;
    std::vector<std::shared_ptr<Album>> albums(const user_id _userId) const override;
    std::vector<std::shared_ptr<Photo>> photos(const album_id _albumId) const override;

    size_t photosCount(const album_id albumId) const override;
    QString firstThumbnailUrl(const album_id albumId) const override;

private:

    void load() override;

    Downloader* m_downloader;

    UsersDict m_users;
    AlbumsDict m_albums;
    PhotosDict m_photos;
};

}
