#include "httpmgr.h"

HttpMgr::HttpMgr()
{

    connect(this,&HttpMgr::sig_http_finish,this,&HttpMgr::slot_http_finish);
}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
    QByteArray data=QJsonDocument(json).toJson();
    QNetworkAccessManager* manager=new QNetworkAccessManager;
    QNetworkRequest* request=new QNetworkRequest;
    request->setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request->setHeader(QNetworkRequest::ContentLengthHeader,data.length());
    request->setUrl(url);
    std::shared_ptr<HttpMgr> self=shared_from_this();
    QNetworkReply* reply=manager->post(*request,data);
    connect(reply,&QNetworkReply::finished,this,[self,req_id,mod,reply](){
        if(reply->error()!=QNetworkReply::NoError)
        {
            emit self->sig_http_finish(req_id,"",ErrorCodes::ERR_NETWORK,mod);
            reply->deleteLater();
            return;
        }
        QString res=reply->readAll();
        emit self->sig_http_finish(req_id,res,ErrorCodes::SUCCESS,mod);
        reply->deleteLater();
        return;

    });
}

HttpMgr::~HttpMgr()
{
    qDebug()<<"delete htpmgr";
}

void HttpMgr::HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod)
{
    if(mod==Modules::REGISTERMOD)
    {
        emit sig_reg_mod_finish(id,res,err);
    }
}
