#ifndef LOGIN_H
#define LOGIN_H

#include<QWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QDebug>
#include<QJsonObject>
#include<QMap>
#include<functional>
#include<memory>
#include"httpmgr.h"
#include"clickedlabel.h"
class Login:public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ClickedLabel* forget_label=nullptr;
    ~Login();
public slots:
    void registHandle();
    void loginClick();
    void slot_login_mod_finish(ReqId id, QString res, ErrorCodes err);
    void slot_tcp_con_finish(bool bsuccess);
private:
    QLineEdit* email=nullptr;
    QLineEdit* pw=nullptr;
    int uid_;
    QString token_;
    void initHttpHandlers();
    QMap<ReqId,std::function<void(QJsonObject)>> _handlers;
signals:
    //注册信号
    void toRegist();
    void toResetPwd();
    void sig_connect_tcp(ServerInfo serverInfo);

};

#endif // LOGIN_H
