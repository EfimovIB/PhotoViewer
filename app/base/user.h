#pragma once

#include <QString>
#include "types.h"

struct User
{
    User(user_id _id = 0, QString _name = "", QString _userName = "")
      : id(_id)
      , name(std::move(_name))
      , userName(std::move(_userName))
    {}

    user_id id = 0;
    QString name;
    QString userName;
    QString email;
    struct Adress
    {
        QString street;
        QString suite;
        QString city;
        QString zipcode;
        struct Geo
        {
            QString lat;
            QString lng;
        } geo;
    } address;
    QString phone;
    QString website;
    struct Company {
        QString name;
        QString catchPhrase;
        QString bs;
    } company;
};
