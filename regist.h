#ifndef REGIST_H
#define REGIST_H
#include<QWidget>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QStyle>
#include<QDebug>
#include<global.h>
#include<QJsonDocument>
#include<QJsonObject>
#include<QMap>
#include"httpmgr.h"

class Regist : public QWidget
{
    Q_OBJECT
public:
    explicit Regist(QWidget *parent = nullptr);
private:
    QLabel* err_tip=nullptr;
    QLineEdit* user=nullptr;
    QLineEdit* email=nullptr;
    QLineEdit* pw=nullptr;
    QLineEdit* pw2=nullptr;
    QLineEdit* check=nullptr;
    void showTip(QString message,bool b_ok);
    void initHttpHandlers();
    QMap<ReqId,std::function<void(QJsonObject&)>> _handlers;
private slots:
    void getChectClick();
    void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
signals:
    void noToLogin();

};

#endif // REGIST_H
