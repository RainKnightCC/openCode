#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QMap>
#include <QVariant>
#include <QStringList>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>

class HttpClientPrivate;

class HttpClient
{
public:
    HttpClient(const QString &url);
    ~HttpClient();

    HttpClient &manager(QNetworkAccessManager *manager);
    HttpClient &debug(bool debug);
    HttpClient &param(const QString &name, const QVariant &value);
    HttpClient &params(const QMap<QString, QVariant> &ps);
    HttpClient &json(const QString &json);
    HttpClient &header(const QString &name, const QString &value);
    HttpClient &headers(const QMap<QString, QString> nameValues);
    HttpClient &success(std::function<void(const QString &)> successHandler);
    HttpClient &fail(std::function<void(const QString &, int)> failHandler);
    HttpClient &complete(std::function<void ()> completeHandler);
    HttpClient &charset(const QString &cs);

    void get();
    void post();
    void put();
    void remove();
    void download(const QString &savePath);
    void upload(const QString &path);
    void upload(const QByteArray &data);
    void upload(const QStringList &paths);

private:
    HttpClientPrivate *d_ptr;

};

#endif // HTTPCLIENT_H
