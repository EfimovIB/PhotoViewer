#pragma once

#include "data_source.h"

class DataSourceNull
  : public DataSource
{
public:

    DataSourceNull(QObject* parent);

    std::vector<std::shared_ptr<User>> users() const override;
    std::vector<std::shared_ptr<Album>> albums(const user_id _user_id) const override;
    std::vector<std::shared_ptr<Photo>> photos(const album_id _album_id) const override;

    size_t photosCount(const album_id albumId) const override;
    QString firstThumbnailUrl(const album_id albumId) const override;

private:

    void load() override {}
};
