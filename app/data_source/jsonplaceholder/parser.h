#pragma once

#include <map>
#include <vector>
#include <list>

#include <QString>

#include "base/types.h"

class QJsonObject;
class QJsonArray;

struct Album;
struct User;
struct Photo;

namespace jsph {

class Parser
{
public:

    static bool parseUsers(std::map<user_id, std::shared_ptr<User>>& _users, const QString& _data);
    static bool parseAlbums(std::map<user_id, std::map<album_id, std::shared_ptr<Album>>>& _albums, const QString& _data);
    static bool parsePhotos(std::map<album_id, std::map<photo_id, std::shared_ptr<Photo>>>& _photos, const QString& _data);

private:

    static std::shared_ptr<User> toUser(const QJsonObject& obj);
    static std::shared_ptr<Album> toAlbum(const QJsonObject& obj);
    static std::shared_ptr<Photo> toPhoto(const QJsonObject& obj);

    static bool hasKeys(const QJsonObject& obj, const std::list<QString>& keys);
    static bool getArray(const QString& _data, QJsonArray& _array);
};

}
