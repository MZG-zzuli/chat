#ifndef LOGIN_H
#define LOGIN_H

#include<QWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QDebug>
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
signals:
    //注册信号
    void toRegist();
    void toResetPwd();

};

#endif // LOGIN_H
