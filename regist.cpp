#include "regist.h"

Regist::Regist(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* mainLayout=new QVBoxLayout;
    setLayout(mainLayout);
    mainLayout->setAlignment(Qt::AlignCenter);
    setMaximumSize(250,400);
    mainLayout->addStretch(3);
    QHBoxLayout* nameLayout=new QHBoxLayout;
    nameLayout->addWidget(new QLabel(QStringLiteral("用  户:")));
    user=new QLineEdit;
    nameLayout->addWidget(user);
    mainLayout->addLayout(nameLayout);


    QHBoxLayout* emailLayout=new QHBoxLayout;
    emailLayout->addWidget(new QLabel(QStringLiteral("邮  箱:")));
    email=new QLineEdit;
    emailLayout->addWidget(email);
    mainLayout->addLayout(emailLayout);

    QHBoxLayout* pwLayout=new QHBoxLayout;
    pwLayout->addWidget(new QLabel(QStringLiteral("密  码:")));
    pw=new QLineEdit;
    pwLayout->addWidget(pw);
    mainLayout->addLayout(pwLayout);

    QHBoxLayout* pw2Layout=new QHBoxLayout;
    pw2Layout->addWidget(new QLabel(QStringLiteral("确  认:")));
    pw2=new QLineEdit;
    pw2Layout->addWidget(pw2);
    mainLayout->addLayout(pw2Layout);

    QHBoxLayout* checkLayout=new QHBoxLayout;
    checkLayout->addWidget(new QLabel(QStringLiteral("验证码:")));
    check=new QLineEdit;
    checkLayout->addWidget(check);
    QPushButton* getCheck=new QPushButton(QStringLiteral("获取"));
    checkLayout->addWidget(getCheck);
    mainLayout->addLayout(checkLayout);

    mainLayout->addStretch(2);

    QHBoxLayout* yesOrNoLayout=new QHBoxLayout;
    mainLayout->addLayout(yesOrNoLayout);
    QPushButton* yesButton=new QPushButton(QStringLiteral("确认"));
    yesOrNoLayout->addWidget(yesButton);
    QPushButton* noButton=new QPushButton(QStringLiteral("取消"));
    yesOrNoLayout->addWidget(noButton);
    connect(noButton,&QPushButton::clicked,this,[=]{
        emit noToLogin();
    });
    mainLayout->addStretch(1);

}
