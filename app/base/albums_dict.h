#pragma once

#include "types.h"
#include "album.h"

#include <map>
#include <memory>
#include <vector>

struct AlbumsDict
{
    std::vector<std::shared_ptr<Album>> findUserAlbums(const user_id _userId) const;

    std::map<user_id, std::map<album_id, std::shared_ptr<Album>>> dict;
};

