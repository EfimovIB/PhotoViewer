#include "parser.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include "base/album.h"
#include "base/user.h"
#include "base/photo.h"

namespace jsph {

bool Parser::parseUsers(std::map<user_id, std::shared_ptr<User>>& _users, const QString& _data)
{
    if (_data.isEmpty())
        return true;

    QJsonArray jsonArray;
    if (!getArray(_data, jsonArray))
    {
        qDebug() << "Parser users error: cannot get array";
        return false;
    }

    std::map<user_id, std::shared_ptr<User>> users;
    foreach (const QJsonValue & value, jsonArray)
    {
        auto user = toUser(value.toObject());
        if (!user)
        {
            qDebug() << "Parser users error: bad user";
            return false;
        }
        if (users.end() != users.find(user->id))
        {
            qDebug() << "Parser users error: 2 albums with same id " << user->id;
            return false;
        }
        users[user->id] = user;
    }
    std::swap(_users, users);
    return true;
}

bool Parser::parseAlbums(std::map<user_id, std::map<album_id, std::shared_ptr<Album>>>& _albums, const QString& _data)
{
    if (_data.isEmpty())
        return true;

    QJsonArray jsonArray;
    if (!getArray(_data, jsonArray))
    {
        qDebug() << "Parser albums error: cannot get array";
        return false;
    }

    std::map<user_id, std::map<album_id, std::shared_ptr<Album>>> albums;
    foreach (const QJsonValue & value, jsonArray)
    {
        auto album = toAlbum(value.toObject());
        if (!album)
        {
            qDebug() << "Parser albums error: bad album";
            return false;
        }
        auto userAlbums = albums.find(album->userId);
        if (userAlbums != albums.end() && userAlbums->second.find(album->id) != userAlbums->second.end())
        {
            qDebug() << "Parser albums error: 2 albums with same id " << album->id;
            return false;
        }
        albums[album->userId][album->id] = album;
    }
    std::swap(_albums, albums);
    return true;
}

bool Parser::parsePhotos(std::map<album_id, std::map<photo_id, std::shared_ptr<Photo>>>& _photos, const QString& _data)
{
    if (_data.isEmpty())
        return true;

    QJsonArray jsonArray;
    if (!getArray(_data, jsonArray))
    {
        qDebug() << "Parser photos error: cannot get array";
        return false;
    }

    std::map<album_id, std::map<photo_id, std::shared_ptr<Photo>>> photos;
    foreach (const QJsonValue & value, jsonArray)
    {
        auto photo = toPhoto(value.toObject());
        if (!photo)
        {
            qDebug() << "Parser photos error: bad photo";
            return false;
        }
        auto albumPhotos = photos.find(photo->albumId);
        if (albumPhotos != photos.end() && albumPhotos->second.find(photo->id) != albumPhotos->second.end())
        {
            qDebug() << "Parser photos error: 2 photos with same id " << photo->id;
            return false;
        }
        photos[photo->albumId][photo->id] = photo;
    }
    std::swap(_photos, photos);
    return true;
}

std::shared_ptr<User> Parser::toUser(const QJsonObject &obj)
{
    static const std::list<QString> keys{"id", "name", "username", "email", "phone", "website", "address", "company"};
    if (!hasKeys(obj, keys))
    {
        qDebug() << "Parser toUser error: key not found";
        return nullptr;
    }

    QJsonObject jsonAdress = obj["address"].toObject();
    static const std::list<QString> adressKeys{"street", "suite", "city", "zipcode", "geo"};
    if (!hasKeys(jsonAdress, adressKeys))
    {
        qDebug() << "Parser toUser error: key not found in address";
        return nullptr;
    }

    QJsonObject jsonGeo = jsonAdress["geo"].toObject();
    static const std::list<QString> geoKeys{"lat", "lng"};
    if (!hasKeys(jsonGeo, geoKeys))
    {
        qDebug() << "Parser toUser error: key not found in geo";
        return nullptr;
    }

    QJsonObject jsonCompany = obj["company"].toObject();
    static const std::list<QString> companyKeys{"name", "catchPhrase", "bs"};
    if (!hasKeys(jsonCompany, companyKeys))
    {
        qDebug() << "Parser toUser error: key not found in company";
        return nullptr;
    }

    auto user = std::make_shared<User>();
    user->id = static_cast<size_t>(obj["id"].toInt());
    user->name = obj["name"].toString();
    user->userName = obj["username"].toString();
    user->email = obj["email"].toString();
    user->phone = obj["phone"].toString();
    user->website = obj["website"].toString();

    user->address.street = jsonAdress["street"].toString();
    user->address.suite = jsonAdress["suite"].toString();
    user->address.city = jsonAdress["city"].toString();
    user->address.zipcode = jsonAdress["zipcode"].toString();

    user->address.geo.lat = jsonGeo["lat"].toString();
    user->address.geo.lng = jsonGeo["lng"].toString();

    user->company.name = jsonCompany["name"].toString();
    user->company.catchPhrase = jsonCompany["catchPhrase"].toString();
    user->company.bs = jsonCompany["bs"].toString();
    return user;
}

std::shared_ptr<Album> Parser::toAlbum(const QJsonObject& obj)
{
    static const std::list<QString> keys{"id", "userId", "title"};
    if (!hasKeys(obj, keys))
    {
        qDebug() << "Parser toAlbum error: key not found";
        return nullptr;
    }

    auto album = std::make_shared<Album>();
    album->id = static_cast<size_t>(obj["id"].toInt());
    album->userId = static_cast<size_t>(obj["userId"].toInt());
    album->title = obj["title"].toString();
    return album;
}

std::shared_ptr<Photo> Parser::toPhoto(const QJsonObject &obj)
{
    static const std::list<QString> keys{"id", "albumId", "title", "url", "thumbnailUrl"};
    if (!hasKeys(obj, keys))
    {
        qDebug() << "Parser toPhoto error: key not found";
        return nullptr;
    }

    auto photo = std::make_shared<Photo>();
    photo->id = static_cast<size_t>(obj["id"].toInt());
    photo->albumId = static_cast<size_t>(obj["albumId"].toInt());
    photo->title = obj["title"].toString();
    photo->url = obj["url"].toString();
    photo->thumbnailUrl = obj["thumbnailUrl"].toString();
    return photo;
}

bool Parser::hasKeys(const QJsonObject& obj, const std::list<QString>& keys)
{
    for (const auto& key : keys)
        if (obj.find(key) == obj.end())
        {
            qDebug() << "Parser hasKey error: cannot find " << key;
            return false;
        }
    return true;
}

bool Parser::getArray(const QString& _data, QJsonArray& _array)
{
    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(_data.toUtf8(), &parseError);
    if (parseError.error)
    {
        qDebug() << "Parser getArray error: " << parseError.errorString();
        return false;
    }
    if (!jsonDocument.isArray())
    {
        qDebug() << "Parser getArray error: not array";
        return false;
    }
    _array = jsonDocument.array();
    return true;
}

}
