#ifndef HTTPMGR_H
#define HTTPMGR_H
#include"Singleton.h"
#include<memory>
#include<QObject>
#include<global.h>
#include<QJsonObject>
#include<QJsonDocument>
#include<QNetworkAccessManager>
#include<QNetworkRequest>
#include<QNetworkReply>

class HttpMgr:public QObject,public Singleton<HttpMgr>,public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT

public:
    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);
    ~HttpMgr();
private:
    HttpMgr();
    friend Singleton<HttpMgr>;
private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);         //http完成
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
    void sig_reset_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // HTTPMGR_H
