#pragma once

#include <QString>

#include "types.h"

struct Photo
{
    Photo(photo_id _id = 0, album_id _albumId = 0, QString _title = "", QString _url = "")
      : id (_id)
      , albumId(_albumId)
      , title(std::move(_title))
      , url(_url)
    {}

    photo_id id = 0;
    album_id albumId = 0;
    QString title;
    QString url;
    QString thumbnailUrl;
};
