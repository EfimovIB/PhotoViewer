#pragma once

class QGuiApplication;

class Settings
{
public:

    Settings(const QGuiApplication& app);

    bool mockDataSource() const;

private:

    bool m_mockDataSource = false;
};
