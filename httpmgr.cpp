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
    qDebug()<<"======"<<url;
    connect(reply,&QNetworkReply::finished,this,[self,req_id,mod,reply](){
        if(reply->error()!=QNetworkReply::NoError)
        {
            emit self->sig_http_finish(req_id,"",ErrorCodes::ERR_NETWORK,mod);
            reply->deleteLater();
            qDebug()<<"error http";
            return;
        }
        QString res=reply->readAll();

        qDebug()<<"success http"<<res;
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
    qDebug()<<"http slot1";
    if(mod==Modules::REGISTERMOD)
    {
        qDebug()<<"http slot2";
        emit sig_reg_mod_finish(id,res,err);
    }
    qDebug()<<"http resetmod";
    if(mod==Modules::RESETMOD)
    {
        emit sig_reset_mod_finish(id,res,err);
    }
    qDebug()<<"http login";
    if(mod==Modules::LOGINMOD)
    {
        qDebug()<<"ee";
        emit sig_login_mod_finish(id,res,err);
    }

    qDebug()<<"http slot3";
}
