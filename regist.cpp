#include "regist.h"

Regist::Regist(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* mainLayout=new QVBoxLayout;
    setLayout(mainLayout);
    mainLayout->setAlignment(Qt::AlignCenter|Qt::AlignTop);
    setMaximumSize(250,400);
    mainLayout->addStretch(3);
    QHBoxLayout* errLayout=new QHBoxLayout;
    errLayout->setAlignment(Qt::AlignCenter);
    err_tip=new QLabel(QStringLiteral("错误提示"));
    errLayout->addWidget(err_tip);
    err_tip->setObjectName("err_tip");

    qDebug()<<err_tip->styleSheet();

    err_tip->setProperty("state","normal");
    err_tip->setVisible(false);
    mainLayout->addLayout(errLayout);
    QHBoxLayout* nameLayout=new QHBoxLayout;
    nameLayout->addWidget(new QLabel(QStringLiteral("用  户:"),this));
    user=new QLineEdit(this);
    nameLayout->addWidget(user);
    mainLayout->addLayout(nameLayout);


    QHBoxLayout* emailLayout=new QHBoxLayout;
    emailLayout->addWidget(new QLabel(QStringLiteral("邮  箱:"),this));
    email=new QLineEdit(this);
    emailLayout->addWidget(email);
    mainLayout->addLayout(emailLayout);

    QHBoxLayout* pwLayout=new QHBoxLayout;
    pwLayout->addWidget(new QLabel(QStringLiteral("密  码:"),this));
    pw=new QLineEdit(this);
    pw->setEchoMode(QLineEdit::Password);
    pwLayout->addWidget(pw);
    mainLayout->addLayout(pwLayout);

    QHBoxLayout* pw2Layout=new QHBoxLayout;
    pw2Layout->addWidget(new QLabel(QStringLiteral("确  认:"),this));
    pw2=new QLineEdit(this);
    pw2->setEchoMode(QLineEdit::Password);
    pw2Layout->addWidget(pw2);
    mainLayout->addLayout(pw2Layout);

    QHBoxLayout* checkLayout=new QHBoxLayout;
    checkLayout->addWidget(new QLabel(QStringLiteral("验证码:"),this));
    check=new QLineEdit(this);
    checkLayout->addWidget(check);
    QPushButton* getCheck=new QPushButton(QStringLiteral("获取"),this);
    connect(getCheck,SIGNAL(clicked()),this,SLOT(getChectClick()));
    checkLayout->addWidget(getCheck);
    mainLayout->addLayout(checkLayout);

    mainLayout->addStretch(2);

    QHBoxLayout* yesOrNoLayout=new QHBoxLayout;
    mainLayout->addLayout(yesOrNoLayout);
    QPushButton* yesButton=new QPushButton(QStringLiteral("确认"),this);
    yesOrNoLayout->addWidget(yesButton);
    QPushButton* noButton=new QPushButton(QStringLiteral("取消"),this);
    yesOrNoLayout->addWidget(noButton);
    connect(noButton,&QPushButton::clicked,this,[=]{
        emit noToLogin();
    });
    mainLayout->addStretch(1);

    initHttpHandlers();
}

void Regist::showTip(QString message,bool b_ok)
{
    err_tip->setText(message);
    err_tip->setVisible(true);
    if(b_ok){
        err_tip->setProperty("state","normal");

    }else {
        err_tip->setProperty("state","err");
    }
    repolish(err_tip);
}

void Regist::initHttpHandlers()
{
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE,[this](QJsonObject& obj){    //处理验证码
        int error=obj["error"].toInt();
        if(error!=ErrorCodes::SUCCESS)
        {
            showTip(QStringLiteral("参数错误"),false);
            return;
        }
        QString email=obj["email"].toString();
        showTip(QStringLiteral("验证码已发送，注意查收"),true);
        qDebug()<<"emailCode:"<<email;
        return;
    });

}

void Regist::getChectClick()
{
    QString password1=pw->text();
    QString password2=pw2->text();

    if(password1!=password2)
    {
        showTip(QStringLiteral("密码不一致"),false);
        return;
    }
    if(password1=="")
    {
        showTip(QStringLiteral("密码不能为空"),false);
        return;
    }
    QString exp="^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";
    QRegExp regexp(exp);
    if(!regexp.exactMatch(email->text()))
    {
        showTip(QStringLiteral("邮箱格式错误"),false);
        return;
    }
    err_tip->setVisible(false);
    //处理http
    QJsonObject jsonObj;
    jsonObj["email"]=email->text();
    QString url="http://127.0.0.1/get_varifycode";
    std::shared_ptr<HttpMgr> httpMgr=HttpMgr::getInstance();
    httpMgr->PostHttpReq(url,jsonObj,ReqId::ID_GET_VARIFY_CODE,Modules::REGISTERMOD);
    connect(httpMgr.get(),&HttpMgr::sig_reg_mod_finish,this,&Regist::slot_reg_mod_finish);


}

void Regist::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err!=ErrorCodes::SUCCESS)
    {
        showTip(QStringLiteral("网络错误"),false);
        return;
    }
    QJsonDocument jsondoc=QJsonDocument::fromJson(res.toUtf8());
    if(jsondoc.isNull())
    {
        showTip(QStringLiteral("json解析错误"),false);
        return;
    }
    if(!jsondoc.isObject())
    {
        showTip(QStringLiteral("json解析错误"),false);
        return;
    }
    QJsonObject jsonObj=jsondoc.object();
    //处理
    _handlers[id](jsonObj);
    return;
}
