#pragma once

#include "types.h"
#include "photo.h"

#include <map>
#include <memory>
#include <vector>

struct PhotosDict
{
    std::vector<std::shared_ptr<Photo>> findAlbumPhotos(const album_id _albumId) const;

    size_t photosCount(const album_id albumId) const;
    QString firstThumbnailUrl(const album_id albumId) const;

    std::map<album_id, std::map<photo_id, std::shared_ptr<Photo>>> dict;
};
