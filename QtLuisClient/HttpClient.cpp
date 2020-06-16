#include "HttpClient.h"

#include <QDebug>
#include <QFile>
#include <QHash>
#include <QUrlQuery>
#include <QHttpPart>
#include <QHttpMultiPart>

enum class HttpClientRequestMethod {
    GET, POST, PUT, DELETE, UPLOAD
};

class HttpClientPrivateCache {
public:
    std::function<void (const QString &)>   successHandler = nullptr;
    std::function<void (const QString &, int)>    failHandler = nullptr;
    std::function<void ()>                           completeHandler = nullptr;
    bool debug = false;
    bool internal = false;
    QString charset;
    QNetworkAccessManager *manager = nullptr;
};

class HttpClientPrivate {
    friend class HttpClient;

    HttpClientPrivate(const QString &url);
    ~HttpClientPrivate();

    HttpClientPrivateCache cache();

    QNetworkAccessManager *getManager();
    static QNetworkRequest createRequest(HttpClientPrivate *d, HttpClientRequestMethod method);

    static void executeQuery(HttpClientPrivate *d, HttpClientRequestMethod method);
    static void upload(HttpClientPrivate *d, const QStringList &path, const QByteArray &data);
    static void download(HttpClientPrivate *d, const QString &savePath);
    static void download(HttpClientPrivate *d, std::function<void (const QByteArray &)> readyRead);

    static QString readReply(QNetworkReply *reply, const QString &charset = "UTF-8");
    static void handleFinish(HttpClientPrivateCache cache, QNetworkReply *reply, const QString &successMessage, const QString &failMessage);

    QString url;
    QString json;
    QUrlQuery params;
    QString charset = "UTF-8";
    QHash<QString, QString> headers;
    QNetworkAccessManager *manager = nullptr;

    bool useJson = false;
    bool debug = false;
    bool internal = true;

    std::function<void (const QString &)>   successHandler = nullptr;
    std::function<void (const QString &, int)>    failHandler = nullptr;
    std::function<void ()>                           completeHandler = nullptr;

};

HttpClientPrivate::HttpClientPrivate(const QString &url) : url(url) {

}

HttpClientPrivate::~HttpClientPrivate() {
    manager = nullptr;
    successHandler = nullptr;
    failHandler = nullptr;
    completeHandler = nullptr;
}

HttpClientPrivateCache HttpClientPrivate::cache() {
    HttpClientPrivateCache cache;
    cache.successHandler = successHandler;
    cache.failHandler = failHandler;
    cache.completeHandler = completeHandler;
    cache.debug = debug;
    cache.internal = internal;
    cache.charset = charset;
    cache.manager = getManager();

    return cache;
}

void HttpClientPrivate::executeQuery(HttpClientPrivate *d, HttpClientRequestMethod method) {
    HttpClientPrivateCache cache = d->cache();

    QNetworkRequest request = HttpClientPrivate::createRequest(d, method);
    QNetworkReply *reply = nullptr;

    switch(method) {
    case HttpClientRequestMethod::GET:
        reply = cache.manager->get(request);
        break;
    case HttpClientRequestMethod::POST:
        reply = cache.manager->post(request, d->useJson ? d->json.toUtf8() : d->params.toString(QUrl::FullyEncoded).toUtf8());
        break;
    case HttpClientRequestMethod::PUT:
        reply = cache.manager->put(request, d->useJson ? d->json.toUtf8() : d->params.toString(QUrl::FullyEncoded).toUtf8());
        break;
    case HttpClientRequestMethod::DELETE:
        reply = cache.manager->deleteResource(request);
        break;
    default:
        break;
    }

    QObject::connect(reply, &QNetworkReply::finished, [=] {
        QString successMessage = HttpClientPrivate::readReply(reply, cache.charset.toUtf8());
        QString failMessage = reply->errorString();
        HttpClientPrivate::handleFinish(cache, reply, successMessage, failMessage);
    });
}

void HttpClientPrivate::download(HttpClientPrivate *d, const QString &savePath) {

}

void HttpClientPrivate::download(HttpClientPrivate *d, std::function<void (const QByteArray &)> readyRead) {

}

void HttpClientPrivate::upload(HttpClientPrivate *d, const QStringList &path, const QByteArray &data) {

}


QNetworkAccessManager *HttpClientPrivate::getManager() {
    return internal ? new QNetworkAccessManager : manager;
}



QNetworkRequest HttpClientPrivate::createRequest(HttpClientPrivate *d, HttpClientRequestMethod method) {

    bool get = method == HttpClientRequestMethod::GET;
    bool upload = method ==HttpClientRequestMethod::UPLOAD;
    bool withForm = !get && !upload && !d->useJson;
    bool withJson = !get && !upload && d->useJson;

    if(get && !d->params.isEmpty()) {
        d->url += "?" + d->params.toString(QUrl::FullyDecoded);
    }

    if(d->debug) {
        qDebug().noquote() << "[website] : " << d->url;

        if(withJson) {
            qDebug().noquote() << "[parameter] : " << d->json;
        }else if(withForm || upload) {
            QList<QPair<QString, QString>> paramItems = d->params.queryItems();
            QString buffer;

            for(int i=0;i < paramItems.size(); ++i) {
                QString name = paramItems.at(i).first;
                QString value = paramItems.at(i).second;

                if(0 == i) {
                    buffer += QString("[parameter] %1=%2 \n").arg(name).arg(value);
                }else{
                    buffer += QString("                     %1=%2 \n").arg(name).arg(value);
                }
            }

            if(!buffer.isEmpty()) {
                qDebug().noquote() << buffer;
            }
        }
    }

    if(withForm) {
        d->headers["Content-Type"] = "application/x-www-form-urlencoded";
    }else if(withJson) {
        d->headers["Content-Type"] = "application/json; charset=utf-8";
    }

    QNetworkRequest request(QUrl(d->url));
    for(auto i = d->headers.cbegin(); i != d->headers.cend(); ++i) {
        request.setRawHeader(i.key().toUtf8(), i.value().toUtf8());
    }

    return request;
}

QString HttpClientPrivate::readReply(QNetworkReply *reply, const QString &charset) {
    QTextStream in(reply);
    QString result;

    in.setCodec(charset.toUtf8());

    while(!in.atEnd()) {
        result += in.readLine();
    }
    return result;
}


void HttpClientPrivate::handleFinish(HttpClientPrivateCache cache, QNetworkReply *reply, const QString &successMessage, const QString &failMessage) {

    if(reply->error() == QNetworkReply::NoError) {
        if(cache.debug) {
            qDebug().noquote() << QString("[finish] success: %1").arg(successMessage);
        }

        if(nullptr != cache.successHandler) {
            cache.successHandler(successMessage);
        }
    }else{
        if(cache.debug) {
            qDebug().noquote() << QString("[finish] fail: %1").arg(failMessage);
        }

        if(nullptr != cache.failHandler) {
            cache.failHandler(failMessage, reply->error());
        }
    }

    if(nullptr != reply) {
        reply->deleteLater();
    }

    if(cache.internal && nullptr != cache.manager) {
        cache.manager->deleteLater();
    }
}


HttpClient::HttpClient(const QString &url) : d_ptr(new HttpClientPrivate(url))
{

}

HttpClient::~HttpClient() {
    delete d_ptr;
}

HttpClient &HttpClient::manager(QNetworkAccessManager *manager) {
    d_ptr->manager = manager;
    d_ptr->internal = (nullptr == manager);

    return *this;
}

HttpClient &HttpClient::debug(bool debug) {
    d_ptr->debug = debug;
    return *this;
}

HttpClient &HttpClient::param(const QString &name, const QVariant &value) {
    d_ptr->params.addQueryItem(name, value.toString());

    return *this;
}

HttpClient &HttpClient::params(const QMap<QString, QVariant> &ps) {
    for(auto iter = ps.cbegin(); iter != ps.cend(); ++ iter) {
        d_ptr->params.addQueryItem(iter.key(), iter.value().toString());
    }

    return *this;
}


HttpClient &HttpClient::json(const QString &json) {
    d_ptr->json = json;
    d_ptr->useJson = true;

    return *this;
}

HttpClient &HttpClient::header(const QString &name, const QString &value) {
    d_ptr->headers[name] = value;
    return *this;
}


HttpClient &HttpClient::headers(const QMap<QString, QString> nameValues) {
    for(auto i = nameValues.cbegin(); i != nameValues.cend(); ++i) {
        d_ptr->headers[i.key()] = i.value();
    }

    return *this;
}

HttpClient &HttpClient::success(std::function<void (const QString &)> successHandler) {
    d_ptr->successHandler = successHandler;

    return *this;
}


HttpClient &HttpClient::fail(std::function<void (const QString &, int)> failHandler) {
    d_ptr->failHandler = failHandler;

    return *this;
}

HttpClient &HttpClient::complete(std::function<void ()> completeHandler) {
    d_ptr->completeHandler = completeHandler;

    return *this;
}

HttpClient &HttpClient::charset(const QString &cs) {
    d_ptr->charset = cs;

    return *this;
}

void HttpClient::get() {
    HttpClientPrivate::executeQuery(d_ptr, HttpClientRequestMethod::GET);
}

void HttpClient::post() {
    HttpClientPrivate::executeQuery(d_ptr, HttpClientRequestMethod::POST);
}

void HttpClient::put() {
    HttpClientPrivate::executeQuery(d_ptr, HttpClientRequestMethod::PUT);
}

void HttpClient::remove() {
    HttpClientPrivate::executeQuery(d_ptr, HttpClientRequestMethod::DELETE);
}

void HttpClient::download(const QString &savePath) {
    HttpClientPrivate::download(d_ptr, savePath);
}

void HttpClient::upload(const QString &path) {
    QStringList paths = {path};
    HttpClientPrivate::upload(d_ptr, paths, QByteArray());
}

void HttpClient::upload(const QByteArray &data) {
    HttpClientPrivate::upload(d_ptr, QStringList(), data);
}

void HttpClient::upload(const QStringList &paths) {
    HttpClientPrivate::upload(d_ptr, paths, QByteArray());
}

