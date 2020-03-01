#pragma once

class DataSource;
class QObject;

class DataSourceFactory
{
public:
    enum class Type
    {
        JSONPlaceholder
      , Mock
    };

    static DataSource* createDataSource(QObject* parent, Type type);
};

