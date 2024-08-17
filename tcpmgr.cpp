#include "tcpmgr.h"
#include<QDebug>
#include<QDataStream>
TcpMgr::TcpMgr(QObject *parent)
    : QObject{parent},host_(""),port_(0),b_recv_pending_(false),message_id_(0),message_len_(0)
{
    connect(&socket_,&QTcpSocket::connected,[&](){
        emit sig_con_success(true);
    });
    connect(&socket_,&QTcpSocket::readyRead,[&](){
        buffer_.append(socket_.readAll());
        QDataStream stream(&buffer_,QIODevice::ReadOnly);
        stream.setVersion(QDataStream::Qt_5_0);
        forever
        {
            if(!b_recv_pending_)
            {
                if(buffer_.size()<static_cast<int>(sizeof(quint16)*2))
                {
                    return;
                }
                stream>>message_id_>>message_len_;
                buffer_=buffer_.mid(sizeof(quint16)*2);
                if(buffer_.size()<message_len_)
                {
                    b_recv_pending_=true;
                    return;
                }
                b_recv_pending_=false;
                QByteArray messageBody=buffer_.mid(0,message_len_);
                qDebug()<<"recv messageBody:"<<messageBody;
                buffer_=buffer_.mid(message_len_);
            }
        }
    });
    connect(&socket_, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred), [&](QAbstractSocket::SocketError socketError) {
        Q_UNUSED(socketError)
        qDebug() << "Error:" << socket_.errorString();
    });
    connect(&socket_,&QTcpSocket::disconnected,[&](){
        qDebug()<<"connect destroy";
    });
    connect(this,&TcpMgr::sig_send_data,this,&TcpMgr::slot_send_date);



}

void TcpMgr::slot_tcp_connect(ServerInfo serverInfo)
{
    host_=serverInfo.Host;
    port_=static_cast<quint16>(serverInfo.Port.toUInt());
    socket_.connectToHost(host_,port_);
}

void TcpMgr::slot_send_date(ReqId reqId, QString data)
{
    quint16 id=reqId;
    QByteArray dataBytes=data.toUtf8();
    quint16 len=static_cast<quint16>(data.size());
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    //set network byte order
    out.setByteOrder(QDataStream::BigEndian);
    out<<id<<len;
    block.append(data);
    socket_.write(block);
}
