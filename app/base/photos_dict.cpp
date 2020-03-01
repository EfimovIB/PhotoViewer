#include "photos_dict.h"

std::vector<std::shared_ptr<Photo>> PhotosDict::findAlbumPhotos(const album_id _albumId) const
{
    auto albumPhotos = dict.find(_albumId);
    if (albumPhotos == dict.end())
        return {};

    const std::map<photo_id, std::shared_ptr<Photo>>& photosMap = albumPhotos->second;
    std::vector<std::shared_ptr<Photo>> photos;
    photos.reserve(photosMap.size());

    std::transform (photosMap.begin(), photosMap.end(), back_inserter(photos),
        [] (const std::pair<photo_id, std::shared_ptr<Photo>>& pair)
        {
            return pair.second;
        });

    return photos;
}

size_t PhotosDict::photosCount(const album_id albumId) const
{
    auto pair = dict.find(albumId);
    if (dict.end() == pair)
        return 0;
    return pair->second.size();
}

QString PhotosDict::firstThumbnailUrl(const album_id albumId) const
{
    auto pair = dict.find(albumId);
    if (dict.end() == pair)
        return "";
    return pair->second.begin()->second->thumbnailUrl;
}
