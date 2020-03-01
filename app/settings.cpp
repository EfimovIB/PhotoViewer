#include "settings.h"

#include <QGuiApplication>
#include <QCommandLineParser>

Settings::Settings(const QGuiApplication& app)
{
    QCommandLineParser parser;
    QCommandLineOption mockDataSourceOption("m", QCoreApplication::translate("main", "Use mock data source for testing"));
    parser.addOption(mockDataSourceOption);
    parser.process(app);
    m_mockDataSource = parser.isSet(mockDataSourceOption);
}

bool Settings::mockDataSource() const
{
    return m_mockDataSource;
}
