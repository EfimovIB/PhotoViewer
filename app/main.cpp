#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "data_source/data_source_factory.h"
#include "model/album_model.h"
#include "model/photo_model.h"
#include "model/user_model.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Settings settings(app);
    auto dataSourceType = settings.mockDataSource() ? DataSourceFactory::Type::Mock : DataSourceFactory::Type::JSONPlaceholder;

    DataSource* dataSource = DataSourceFactory::createDataSource(&app, dataSourceType);

    UserModel userModel(dataSource);
    AlbumModel albumModel(dataSource);
    PhotoModel photoModel(dataSource);

    QQmlApplicationEngine engine;
    engine.addImportPath(":/qml");
    engine.rootContext()->setContextProperty("albumModel", &albumModel);
    engine.rootContext()->setContextProperty("userModel", &userModel);
    engine.rootContext()->setContextProperty("photoModel", &photoModel);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl)
    {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
