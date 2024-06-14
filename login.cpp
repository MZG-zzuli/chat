﻿#include "login.h"

Login::Login(QWidget *parent)
    : QWidget{parent}
{

    QVBoxLayout* mainLayout=new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignCenter);
    setMaximumSize(250,400);
    setLayout(mainLayout);
    QLabel* img=new QLabel;
    img->setText("<img src=\"qrc:/img/qq_pic_merged_1718351502937.jpg\" width=200 height=200>");
    QHBoxLayout* imgLayout=new QHBoxLayout;
    imgLayout->setAlignment(Qt::AlignHCenter);
    imgLayout->addWidget(img);
    mainLayout->addLayout(imgLayout);
    QHBoxLayout* nameLayout=new QHBoxLayout;
    nameLayout->addWidget(new QLabel(QStringLiteral("用户:")));
    QLineEdit* name=new QLineEdit;
    nameLayout->addWidget(name);
    mainLayout->addLayout(nameLayout);

    QHBoxLayout* pwLayout=new QHBoxLayout;
    pwLayout->addWidget(new QLabel(QStringLiteral("密码:")));
    QLineEdit* pw=new QLineEdit;
    pwLayout->addWidget(pw);
    mainLayout->addLayout(pwLayout);

    QHBoxLayout* forgetLayout=new QHBoxLayout;
    forgetLayout->setAlignment(Qt::AlignRight);
    QPushButton* forgetButton=new QPushButton(QStringLiteral("忘记密码"));
    forgetLayout->addWidget(forgetButton);
    mainLayout->addLayout(forgetLayout);

    QPushButton* loginButton=new QPushButton(QStringLiteral("登录"));
    mainLayout->addWidget(loginButton);

    QPushButton* registButton=new QPushButton(QStringLiteral("注册"));
    mainLayout->addWidget(registButton);
    //connect(registButton,SIGNAL(clicked(bool)),this,SLOT(registHandle()));
    connect(registButton,&QPushButton::clicked,this,[=]{
        emit toRegist();
    });



}

Login::~Login()
{
    qDebug()<<"===";
}

void Login::registHandle()
{
    emit toRegist();
}
