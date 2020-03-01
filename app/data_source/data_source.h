#pragma once

#include <memory>
#include <vector>

#include <QObject>

#include "base/types.h"

struct User;
struct Album;
struct Photo;
class DataSourceFactory;

class DataSource
  : public QObject
{
    Q_OBJECT

public:

    DataSource(QObject* parent) : QObject(parent) {}
    virtual ~DataSource() = default;

    virtual std::vector<std::shared_ptr<User>> users() const = 0;
    virtual std::vector<std::shared_ptr<Album>> albums(const user_id _user_id) const = 0;
    virtual std::vector<std::shared_ptr<Photo>> photos(const album_id _album_id) const = 0;

    virtual size_t photosCount(const album_id albumId) const = 0;
    virtual QString firstThumbnailUrl(const album_id albumId) const = 0;

signals:

    void dataUpdated();

private:

    friend class DataSourceFactory;
    virtual void load() = 0;
};

