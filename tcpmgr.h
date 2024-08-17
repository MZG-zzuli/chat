#ifndef TCPMGR_H
#define TCPMGR_H

#include <QObject>
#include<memory>
#include<QTcpSocket>
#include"Singleton.h"
#include"global.h"
class TcpMgr : public QObject,public Singleton<TcpMgr>,public std::enable_shared_from_this<TcpMgr>
{
    Q_OBJECT
public:
    explicit TcpMgr(QObject *parent = nullptr);
private:
    QTcpSocket socket_;
    QString host_;
    uint16_t port_;
    QByteArray buffer_;
    bool b_recv_pending_;
    quint16 message_id_;
    quint16 message_len_;
public slots:
    void slot_tcp_connect(ServerInfo serverInfo);
    void slot_send_date(ReqId reqId,QString data);

signals:
    void sig_con_success(bool b_success);
    void sig_send_data(ReqId reqId,QString data);

};

#endif // TCPMGR_H
