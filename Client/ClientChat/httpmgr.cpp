#include "httpmgr.h"


HttpMgr::HttpMgr() {
    connect(this, &HttpMgr::sig_http_finish,this,&HttpMgr::slot_http_finish);
}

HttpMgr::~HttpMgr()
{

}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentTypeHeader,QByteArray::number(data.length()));
    auto self = shared_from_this();
    QNetworkReply * reply = _manager.post(request, data);
    connect(reply, &QNetworkReply::finished, [self,reply,req_id,mod](){
        //处理错误情况
        if(reply->error()!=QNetworkReply::NoError){
            qDebug()<<reply->errorString();
            //发送信号通知完成
            emit self->sig_http_finish(req_id,"",ErrorCode::ERR_NETWORK,mod);
            reply->deleteLater();
            return;
        }
        //无错误
        QString res = reply->readAll();
        //发送信号通知完成
        emit self->sig_http_finish(req_id,res,ErrorCode::SUCCESS,mod);
        return;
    });
}

void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCode err, Modules mod)
{
    if(mod == Modules::REGISTERMOD){
        //发送信号通知指定模块http的相应结束了
        emit sig_reg_mod_finish(id,res,err);
    }

    if(mod == Modules::RESETMOD){
        //发送信号通知指定模块http响应结束
        emit sig_reset_mod_finish(id,res,err);
    }
}
