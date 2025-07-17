#ifndef HTTPMGR_H
#define HTTPMGR_H
#include "singleton.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include "global.h"

class HttpMgr:public QObject,public Singleton<HttpMgr>,
                public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
public:
    ~HttpMgr();
   HttpMgr();
private:
    friend class Singleton<HttpMgr>;

    QNetworkAccessManager _manager;
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);
private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCode err, Modules mod);
signals:
    void sig_http_finish(ReqId id, QString res, ErrorCode err, Modules mod);
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCode err);
};

#endif // HTTPMGR_H
