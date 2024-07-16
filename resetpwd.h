#ifndef RESETPWD_H
#define RESETPWD_H

#include <QWidget>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QLabel>
#include<QPushButton>
#include<QMap>
#include<QJsonObject>
#include<QJsonDocument>
#include<QDebug>
#include"timerbtn.h"
#include"clickedlabel.h"
#include"httpmgr.h"
class ResetPwd : public QWidget
{
    Q_OBJECT
public:
    explicit ResetPwd(QWidget *parent = nullptr);
private:
    QLabel* err_tip=nullptr;
    QLineEdit* name=nullptr;
    QLineEdit* email=nullptr;
    QLineEdit* verifycode=nullptr;
    QLineEdit* newpwd=nullptr;
    TimerBtn* getVerify=nullptr;
    void showTip(const QString &str,bool b_ok);
    void initHandlers();
    bool checkUserValid();
    bool checkPassValid();
    bool checkEmailValid();
    void getVerifyCode();
    void on_sure_btn_clicked();
    void slot_reset_mod_finish(ReqId id, QString res, ErrorCodes err);
    QMap<ReqId,std::function<void(QJsonObject&)>> _handlers;
signals:
    void toLogin();

};

#endif // RESETPWD_H
