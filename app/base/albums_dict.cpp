#include "albums_dict.h"

std::vector<std::shared_ptr<Album>> AlbumsDict::findUserAlbums(const user_id _userId) const
{
    auto userAlbums = dict.find(_userId);
    if (userAlbums == dict.end())
        return {};

    const std::map<album_id, std::shared_ptr<Album>>& albumsMap = userAlbums->second;
    std::vector<std::shared_ptr<Album>> albums;
    albums.reserve(albumsMap.size());

    std::transform (albumsMap.begin(), albumsMap.end(), back_inserter(albums),
        [] (const std::pair<album_id, std::shared_ptr<Album>>& pair)
        {
            return pair.second;
        });

    return albums;
}
