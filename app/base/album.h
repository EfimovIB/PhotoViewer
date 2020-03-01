#pragma once

#include <QString>

#include "types.h"

struct Album
{
    Album(album_id _id = 0, user_id _userId = 0, QString _title = "")
      : id(_id)
      , userId(_userId)
      , title(std::move(_title))
    {}

    album_id id = 0;
    user_id userId = 0;
    QString title;
};
