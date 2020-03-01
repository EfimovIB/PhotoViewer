#include "data_source_null.h"

#include <QDebug>

DataSourceNull::DataSourceNull(QObject* parent)
  : DataSource(parent)
{
}

std::vector<std::shared_ptr<User> > DataSourceNull::users() const
{
    qDebug() << "DataSource broken";
    return {};
}

std::vector<std::shared_ptr<Album> > DataSourceNull::albums(const user_id) const
{
    qDebug() << "DataSource broken";
    return {};
}

std::vector<std::shared_ptr<Photo> > DataSourceNull::photos(const album_id) const
{
    qDebug() << "DataSource broken";
    return {};
}

size_t DataSourceNull::photosCount(const album_id) const
{
    qDebug() << "DataSource broken";
    return 0;
}

QString DataSourceNull::firstThumbnailUrl(const album_id) const
{
    qDebug() << "DataSource broken";
    return {};
}
