#include "data_source/jsonplaceholder/data_source_jsonplaceholder.h"

#include <QDebug>

#include "base/album.h"
#include "downloader.h"
#include "parser.h"
#include "base/photo.h"
#include "base/user.h"

namespace jsph {

DataSourceJsonPlaceholder::DataSourceJsonPlaceholder(QObject* parent)
  : DataSource(parent)
  , m_downloader(new Downloader(this))
{
}

std::vector<std::shared_ptr<User>> DataSourceJsonPlaceholder::users() const
{
    return m_users.toVector();
}

std::vector<std::shared_ptr<Album>> DataSourceJsonPlaceholder::albums(const user_id _userId) const
{
    return m_albums.findUserAlbums(_userId);
}

std::vector<std::shared_ptr<Photo>> DataSourceJsonPlaceholder::photos(const album_id _albumId) const
{
    return m_photos.findAlbumPhotos(_albumId);
}

size_t DataSourceJsonPlaceholder::photosCount(const album_id albumId) const
{
    return m_photos.photosCount(albumId);
}

QString DataSourceJsonPlaceholder::firstThumbnailUrl(const album_id albumId) const
{
    return m_photos.firstThumbnailUrl(albumId);
}

void DataSourceJsonPlaceholder::load()
{
    m_downloader->download({
        {QUrl("https://jsonplaceholder.typicode.com/users"), [this](Downloader::Result error, QString body){ if (!error) Parser::parseUsers(m_users.dict, body); }}
      , {QUrl("https://jsonplaceholder.typicode.com/albums"), [this](Downloader::Result error, QString body){ if (!error) Parser::parseAlbums(m_albums.dict, body); }}
      , {QUrl("https://jsonplaceholder.typicode.com/photos"), [this](Downloader::Result error, QString body){ if (!error) Parser::parsePhotos(m_photos.dict, body); emit dataUpdated(); }}
    });
}

}
