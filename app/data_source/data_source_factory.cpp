#include "data_source_factory.h"

#include <QDebug>

#include "data_source_null.h"
#include "data_source_mock.h"
#include "jsonplaceholder/data_source_jsonplaceholder.h"

DataSource* DataSourceFactory::createDataSource(QObject* parent, Type type)
{
    DataSource* dataSource;

    switch (type)
    {
    case Type::JSONPlaceholder: dataSource = new jsph::DataSourceJsonPlaceholder(parent); break;
    case Type::Mock: dataSource = new DataSourceMock(parent); break;
    }

    if (!dataSource)
    {
        qDebug() << "DataSourceFactory onstruct failed";
        return new DataSourceNull(parent);
    }

    dataSource->load();

    return dataSource;
}
