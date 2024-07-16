#include "registsuccess.h"

RegistSuccess::RegistSuccess(QWidget *parent)
    : QWidget{parent},time{5}
{
    QVBoxLayout* mainLayout=new QVBoxLayout;
    setLayout(mainLayout);
    QHBoxLayout* hlayout=new QHBoxLayout;
    lab=new QLabel(QStringLiteral("注册成功，%1 s后返回登录").arg(time));
    hlayout->addStretch(1);
    hlayout->addWidget(lab);
    hlayout->addStretch(1);
    mainLayout->addStretch(1);
    mainLayout->addLayout(hlayout);
    QLabel *lab2 = new QLabel(QStringLiteral("点击返回按钮返回登陆界面"));
    QHBoxLayout* hlayout2=new QHBoxLayout;
    hlayout2->addStretch(1);
    hlayout2->addWidget(lab2);
    hlayout2->addStretch(1);
    mainLayout->addLayout(hlayout2);
    mainLayout->addStretch(1);
    QHBoxLayout* butlay=new QHBoxLayout;
    butlay->addStretch(1);
    QPushButton* returnLogin=new QPushButton(QStringLiteral("返回登录"));
    butlay->addWidget(returnLogin);
    butlay->addStretch(1);
    mainLayout->addLayout(butlay);
    mainLayout->addStretch(1);
    connect(returnLogin,&QPushButton::clicked,this,[this](){
        emit toLogin();
        timer->stop();
    });
    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,[this](){
        lab->setText(QStringLiteral("注册成功，%1 s后返回登录").arg(time));
        time--;
        if(time<0)
        {
            emit toLogin();
            timer->stop();
        }

    });
    //timer->start(1000);

}

void RegistSuccess::start()
{
    time=5;
    lab->setText(QStringLiteral("注册成功，%1 s后返回登录").arg(time));
    timer->start(1000);

}
