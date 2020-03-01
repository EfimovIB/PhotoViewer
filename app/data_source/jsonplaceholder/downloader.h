#pragma once

#include <QObject>
#include <QUrl>

#include <functional>
class QNetworkReply;
class QNetworkAccessManager;

namespace jsph {

class Downloader
  : public QObject
{
    Q_OBJECT

public:

    Downloader(QObject* parent = nullptr);

    enum Result
    {
        ok,
        failed
    };

    using reply_handler_type = std::function<void(Downloader::Result, QString)>;
    struct Request
    {
        QUrl url;
        reply_handler_type handler;
    };
    void download(const std::list<Request>& requests);

private:

    void invokeRequestPool();

    void replyFinished(QNetworkReply *reply);

    QNetworkAccessManager* m_manager;

    std::list<Request> m_requsetPool;
};

}
