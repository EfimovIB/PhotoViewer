#include "data_source_mock.h"

#include <QDebug>

#include "base/album.h"
#include "base/photo.h"
#include "base/user.h"

DataSourceMock::DataSourceMock(QObject *parent)
  : DataSource(parent)
{
}

std::vector<std::shared_ptr<User>> DataSourceMock::users() const
{
    return m_users;
}

std::vector<std::shared_ptr<Album>> DataSourceMock::albums(const user_id _userId) const
{
    return m_albums.findUserAlbums(_userId);
}

std::vector<std::shared_ptr<Photo>> DataSourceMock::photos(const album_id _albumId) const
{
    return  m_photos.findAlbumPhotos(_albumId);
}

size_t DataSourceMock::photosCount(const album_id albumId) const
{
    return m_photos.photosCount(albumId);
}

QString DataSourceMock::firstThumbnailUrl(const album_id albumId) const
{
    return m_photos.firstThumbnailUrl(albumId);
}

void DataSourceMock::load()
{
    m_users.push_back(std::make_shared<User>(1, "Grace", "Hopper"));
    m_users.push_back(std::make_shared<User>(2, "Robert", "Martin"));
    m_users.push_back(std::make_shared<User>(3, "Tom", "Riddle"));
    m_users.push_back(std::make_shared<User>(4, "Scott", "Meyers"));

    m_albums.dict.insert({1, {
        {1, std::make_shared<Album>(1, 1, "Grace Album 1")}
      , {2, std::make_shared<Album>(2, 1, "Grace Album 2")}
      , {3, std::make_shared<Album>(3, 1, "Grace Album 3")}
    }});

    m_albums.dict.insert({2, {
        {4, std::make_shared<Album>(4, 2, "Robert Album 1")}
      , {5, std::make_shared<Album>(5, 2, "Robert Album 2")}
    }});

    m_albums.dict.insert({3, {
        {6, std::make_shared<Album>(6, 3, "Tom Album 1")}
    }});

    m_photos.dict.insert({1, {
        {1, std::make_shared<Photo>(1, 1, "Grace Album 1 Photo 1", "https://via.placeholder.com/600/92c952")}
      , {2, std::make_shared<Photo>(2, 1, "Grace Album 1 Photo 2", "https://via.placeholder.com/600/771796")}
      , {3, std::make_shared<Photo>(3, 1, "Grace Album 1 Photo 3", "https://via.placeholder.com/600/24f355")}
     }});

    m_photos.dict.insert({2, {
        {4, std::make_shared<Photo>(4, 2, "Grace Album 2 Photo 1", "https://via.placeholder.com/600/d32776")}
      , {5, std::make_shared<Photo>(5, 2, "Grace Album 2 Photo 2", "https://via.placeholder.com/600/f66b97")}
      , {6, std::make_shared<Photo>(6, 2, "Grace Album 2 Photo 3", "https://via.placeholder.com/600/56a8c2")}
     }});

    m_photos.dict.insert({3, {
        {7, std::make_shared<Photo>(7, 3, "Grace Album 3 Photo 1", "https://via.placeholder.com/600/b0f7cc")}
     }});

    m_photos.dict.insert({5, {
        {8, std::make_shared<Photo>(8, 5, "Robert Album 2 Photo 1", "https://via.placeholder.com/600/54176f")}
     }});

    m_photos.dict.insert({6, {
        {9, std::make_shared<Photo>(9, 6, "Robert Album 2 Photo 1", "https://via.placeholder.com/600/51aa97")}
     }});
}
