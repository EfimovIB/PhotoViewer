#include "downloader.h"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>

namespace jsph {

Downloader::Downloader(QObject* parent)
  : QObject(parent)
  , m_manager(new QNetworkAccessManager(this))
{
    connect(m_manager, &QNetworkAccessManager::finished, this, &Downloader::replyFinished);
}

void Downloader::download(const std::list<Downloader::Request> &requests)
{
    bool invokerAlreadyWork = !m_requsetPool.empty();
    m_requsetPool.insert(m_requsetPool.end(), requests.begin(), requests.end());
    if (!invokerAlreadyWork)
        invokeRequestPool();
}

void Downloader::invokeRequestPool()
{
    if (!m_requsetPool.empty())
        m_manager->get(QNetworkRequest(m_requsetPool.front().url));
}

void Downloader::replyFinished(QNetworkReply* reply)
{
    Q_ASSERT(!m_requsetPool.empty());
    const Request& request = m_requsetPool.front();
    if (reply->error())
    {
        qDebug() << "Downloader error '" << reply->errorString() << "' on request " << request.url;
        request.handler(failed, "");
    }
    else
    {
        QString body(reply->readAll());
        request.handler(ok, std::move(body));
    }
    m_requsetPool.pop_front();
    invokeRequestPool();
}

}
