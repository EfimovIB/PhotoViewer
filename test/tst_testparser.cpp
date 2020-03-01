#include <QtTest>

#include "base/album.h"
#include "base/photo.h"
#include "base/user.h"

#include "data_source/jsonplaceholder/parser.h"

class testparser : public QObject
{
    Q_OBJECT

public:

    testparser() = default;

private slots:

    void test_case_album_positive();
    void test_case_album_negative();

    void test_case_photo_positive();
    void test_case_photo_negative();

    void test_case_user_positive();
};

void testparser::test_case_album_positive()
{
    {
        QString data;
        std::map<user_id, std::map<album_id, std::shared_ptr<Album>>> album;
        QVERIFY(jsph::Parser::parseAlbums(album, data));
    }

    {
        QString data = "[{ \"userId\": 1, \"id\": 2, \"title\": \"first album\" }]";
        std::map<user_id, std::map<album_id, std::shared_ptr<Album>>> usersAlbums;
        QVERIFY(jsph::Parser::parseAlbums(usersAlbums, data));
        QVERIFY(usersAlbums.size() == 1);
        QVERIFY(usersAlbums.find(1) != usersAlbums.end());

        auto albums = usersAlbums[1];
        QVERIFY(albums.size() == 1);
        QVERIFY(albums.find(2) != albums.end());

        auto album = albums[2];
        QVERIFY(album->id == 2);
        QVERIFY(album->userId == 1);
        QVERIFY(album->title == "first album");
    }

    {
        QString data = "[{ \"userId\": 1, \"id\": 2, \"title\": \"first album\" }, { \"userId\": 1, \"id\": 4, \"title\": \"second album\" }]";
        std::map<user_id, std::map<album_id, std::shared_ptr<Album>>> usersAlbums;
        QVERIFY(jsph::Parser::parseAlbums(usersAlbums, data));
        QVERIFY(usersAlbums.size() == 1);
        QVERIFY(usersAlbums.find(1) != usersAlbums.end());

        auto albums = usersAlbums[1];
        QVERIFY(albums.size() == 2);
        QVERIFY(albums.find(2) != albums.end());

        auto album = albums[2];
        QVERIFY(album->id == 2);
        QVERIFY(album->userId == 1);
        QVERIFY(album->title == "first album");

        album = albums[4];
        QVERIFY(album->id == 4);
        QVERIFY(album->userId == 1);
        QVERIFY(album->title == "second album");
    }
}

void testparser::test_case_album_negative()
{
    {
        QString data = "[{\"id\": 1, \"title\": \"quidem molestiae enim\" }]";
        std::map<user_id, std::map<album_id, std::shared_ptr<Album>>> album;
        QVERIFY(!jsph::Parser::parseAlbums(album, data));
    }

    {
        QString data = "[{ \"userId\": 1, \"title\": \"quidem molestiae enim\" }]";
        std::map<user_id, std::map<album_id, std::shared_ptr<Album>>> album;
        QVERIFY(!jsph::Parser::parseAlbums(album, data));
    }

    {
        QString data = "[{ \"userId\": 1, \"id\": 1 }]";
        std::map<user_id, std::map<album_id, std::shared_ptr<Album>>> album;
        QVERIFY(!jsph::Parser::parseAlbums(album, data));
    }

    {
        QString data = "{ \"userId\": 1, \"id\": 2, \"title\": \"first album\" }";
        std::map<user_id, std::map<album_id, std::shared_ptr<Album>>> album;
        QVERIFY(!jsph::Parser::parseAlbums(album, data));
    }
}

void testparser::test_case_photo_positive()
{
    {
        QString data;
        std::map<album_id, std::map<photo_id, std::shared_ptr<Photo>>> photos;
        QVERIFY(jsph::Parser::parsePhotos(photos, data));
    }

    {
        QString data = "[ { \"albumId\": 1, \"id\": 1, \"title\": \"title 1\", \"url\": \"https://url.com\", \"thumbnailUrl\": \"https://url2.com\" } ]";
        std::map<album_id, std::map<photo_id, std::shared_ptr<Photo>>> albumsPhotos;
        QVERIFY(jsph::Parser::parsePhotos(albumsPhotos, data));
        QVERIFY(albumsPhotos.size() == 1);
        QVERIFY(albumsPhotos.find(1) != albumsPhotos.end());

        auto photos = albumsPhotos[1];
        QVERIFY(photos.size() == 1);
        QVERIFY(photos.find(1) != photos.end());

        auto photo = photos[1];
        QVERIFY(photo->id == 1);
        QVERIFY(photo->albumId == 1);
        QVERIFY(photo->title == "title 1");
        QVERIFY(photo->url == "https://url.com");
        QVERIFY(photo->thumbnailUrl == "https://url2.com");
    }

    {
        QString data = "[ { \"albumId\": 1, \"id\": 1, \"title\": \"title 1\", \"url\": \"https://url.com\", \"thumbnailUrl\": \"https://url2.com\" }, { \"albumId\": 1, \"id\": 2, \"title\": \"title 2\", \"url\": \"https://url3.com/\", \"thumbnailUrl\": \"https://url4.com/\" } ]";
        std::map<album_id, std::map<photo_id, std::shared_ptr<Photo>>> albumsPhotos;
        QVERIFY(jsph::Parser::parsePhotos(albumsPhotos, data));
        QVERIFY(albumsPhotos.size() == 1);
        QVERIFY(albumsPhotos.find(1) != albumsPhotos.end());

        auto photos = albumsPhotos[1];
        QVERIFY(photos.size() == 2);
        QVERIFY(photos.find(1) != photos.end());

        auto photo = photos[1];
        QVERIFY(photo->id == 1);
        QVERIFY(photo->albumId == 1);
        QVERIFY(photo->title == "title 1");
        QVERIFY(photo->url == "https://url.com");
        QVERIFY(photo->thumbnailUrl == "https://url2.com");

        photo = photos[2];
        QVERIFY(photo->id == 2);
        QVERIFY(photo->albumId == 1);
        QVERIFY(photo->title == "title 2");
        QVERIFY(photo->url == "https://url3.com/");
        QVERIFY(photo->thumbnailUrl == "https://url4.com/");
    }
}

void testparser::test_case_photo_negative()
{
    {
        QString data = "[ { \"id\": 1, \"title\": \"title 1\", \"url\": \"https://url.com\", \"thumbnailUrl\": \"https://url2.com\" } ]";
        std::map<album_id, std::map<photo_id, std::shared_ptr<Photo>>> albumsPhotos;
        QVERIFY(!jsph::Parser::parsePhotos(albumsPhotos, data));
    }

    {
        QString data = "[ { \"albumId\": 1, \"title\": \"title 1\", \"url\": \"https://url.com\", \"thumbnailUrl\": \"https://url2.com\" } ]";
        std::map<album_id, std::map<photo_id, std::shared_ptr<Photo>>> albumsPhotos;
        QVERIFY(!jsph::Parser::parsePhotos(albumsPhotos, data));
    }
    {
        QString data = "[ { \"albumId\": 1, \"id\": 1, \"url\": \"https://url.com\", \"thumbnailUrl\": \"https://url2.com\" } ]";
        std::map<album_id, std::map<photo_id, std::shared_ptr<Photo>>> albumsPhotos;
        QVERIFY(!jsph::Parser::parsePhotos(albumsPhotos, data));
    }
    {
        QString data = "[ { \"albumId\": 1, \"id\": 1, \"title\": \"title 1\", \"thumbnailUrl\": \"https://url2.com\" } ]";
        std::map<album_id, std::map<photo_id, std::shared_ptr<Photo>>> albumsPhotos;
        QVERIFY(!jsph::Parser::parsePhotos(albumsPhotos, data));
    }
    {
        QString data = "[ { \"albumId\": 1, \"id\": 1, \"title\": \"title 1\", \"url\": \"https://url.com\" } ]";
        std::map<album_id, std::map<photo_id, std::shared_ptr<Photo>>> albumsPhotos;
        QVERIFY(!jsph::Parser::parsePhotos(albumsPhotos, data));
    }
}

void testparser::test_case_user_positive()
{
    {
        QString data;
        std::map<user_id, std::shared_ptr<User>> users;
        QVERIFY(jsph::Parser::parseUsers(users, data));
    }

    {
        QString data = "[{ \"id\": 1, \"name\": \"Leanne Graham\", \"username\": \"Bret\", \"email\": \"Sincere@april.biz\", \"address\": { \"street\": \"Kulas Light\", \"suite\": \"Apt. 556\", \"city\": \"Gwenborough\", \"zipcode\": \"92998-3874\", \"geo\": { \"lat\": \"-37.3159\", \"lng\": \"81.1496\" } }, \"phone\": \"770\", \"website\": \"h.org\", \"company\": { \"name\": \"Crona\", \"catchPhrase\": \"Phrase\", \"bs\": \"...\" } }]";
        std::map<user_id, std::shared_ptr<User>> users;
        QVERIFY(jsph::Parser::parseUsers(users, data));
        QVERIFY(users.size() == 1);
        QVERIFY(users.find(1) != users.end());

        auto user = users[1];
        QVERIFY(user->id == 1);
        QVERIFY(user->name == "Leanne Graham");
        QVERIFY(user->userName == "Bret");
        QVERIFY(user->email == "Sincere@april.biz");
        QVERIFY(user->address.street == "Kulas Light");
        QVERIFY(user->address.suite == "Apt. 556");
        QVERIFY(user->address.city == "Gwenborough");
        QVERIFY(user->address.zipcode == "92998-3874");
        QVERIFY(user->address.geo.lat == "-37.3159");
        QVERIFY(user->address.geo.lng == "81.1496");
        QVERIFY(user->phone == "770");
        QVERIFY(user->website == "h.org");
        QVERIFY(user->company.name == "Crona");
        QVERIFY(user->company.catchPhrase == "Phrase");
        QVERIFY(user->company.bs == "...");
    }
}

QTEST_APPLESS_MAIN(testparser)

#include "tst_testparser.moc"
