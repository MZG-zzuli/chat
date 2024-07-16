#include "regist.h"

Regist::Regist(QWidget *parent)
    : QWidget{parent}
{

    std::shared_ptr<HttpMgr> httpMgr=HttpMgr::getInstance();
    connect(httpMgr.get(),&HttpMgr::sig_reg_mod_finish,this,&Regist::slot_reg_mod_finish);
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
    pwvis=new ClickedLabel(this);
    connect(pwvis,&ClickedLabel::clicked,this,[this](){
        if(pwvis->GetCurState()==ClickLbState::Normal)
        {
            pw->setEchoMode(QLineEdit::Password);
        }else
        {
            pw->setEchoMode(QLineEdit::Normal);
        }
    });
    //-----------
    pwvis->SetState("unvisible","unvisible_hover","visible",
                    "visible_hover");
    pwvis->setObjectName("pwvis");
    pwLayout->addWidget(pwvis);
    mainLayout->addLayout(pwLayout);

    QHBoxLayout* pw2Layout=new QHBoxLayout;
    pw2Layout->addWidget(new QLabel(QStringLiteral("确  认:"),this));
    pw2=new QLineEdit(this);
    pw2->setEchoMode(QLineEdit::Password);
    pw2Layout->addWidget(pw2);

    pwvis2=new ClickedLabel;
    connect(pwvis2,&ClickedLabel::clicked,this,[this](){
        if(pwvis2->GetCurState()==ClickLbState::Normal)
        {
            pw2->setEchoMode(QLineEdit::Password);
        }else
        {
            pw2->setEchoMode(QLineEdit::Normal);
        }
    });
    //-----------
    pwvis2->SetState("unvisible","unvisible_hover","visible",
                    "visible_hover");
    pwvis2->setObjectName("pwvis2");
    pw2Layout->addWidget(pwvis2);
    mainLayout->addLayout(pw2Layout);

    QHBoxLayout* checkLayout=new QHBoxLayout;
    checkLayout->addWidget(new QLabel(QStringLiteral("验证码:"),this));
    check=new QLineEdit(this);
    checkLayout->addWidget(check);
    getCheck=new TimerBtn(QStringLiteral("获取"),this);

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
    connect(yesButton,SIGNAL(clicked(bool)),this,SLOT(yesButtonClick()));

    connect(noButton,&QPushButton::clicked,this,[=]{
        emit noToLogin();
    });

    mainLayout->addStretch(1);

    initHttpHandlers();
}

Regist::~Regist()
{
    qDebug()<<"xgreg\n";
}

bool Regist::checkEdit()
{
    QString password1=pw->text();
    QString password2=pw2->text();

    if(password1!=password2)
    {
        showTip(QStringLiteral("密码不一致"),false);
        return false;
    }
    if(password1=="")
    {
        showTip(QStringLiteral("密码不能为空"),false);
        return false;
    }
    QString exp="^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";
    QRegExp regexp(exp);
    if(!regexp.exactMatch(email->text()))
    {
        showTip(QStringLiteral("邮箱格式错误"),false);
        return false;
    }
    err_tip->setVisible(false);
    return true;
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
    _handlers.insert(ReqId::ID_GET_VERIFY_CODE,[this](QJsonObject& obj){    //处理验证码
        int error=obj["error"].toInt();
        if(error!=ErrorCodes::SUCCESS)
        {
            showTip(QStringLiteral("网络错误"),false);
            return;
        }
        QString email=obj["email"].toString();
        showTip(QStringLiteral("验证码已发送，注意查收"),true);
        qDebug()<<"emailCode:"<<email;
        return;
    });
    _handlers.insert(ReqId::ID_REG_USER,[this](QJsonObject& obj){
        int error=obj["error"].toInt();
        if(error==ErrorCodes::VerifyCodeErr)
        {
            showTip(QStringLiteral("验证码错误"),false);
        }
        if(error==ErrorCodes::VerifyExpired)
        {
            showTip(QStringLiteral("验证码过期"),false);

        }
        if(error==ErrorCodes::UserExist)
        {
            showTip(QStringLiteral("用户已存在"),false);

        }
        if(error!=ErrorCodes::SUCCESS)
        {
            showTip(QStringLiteral("参数错误"),false);
            return;
        }
        showTip(tr("用户注册成功"), true);
        emit registOk();
        qDebug()<<"reg success";


    });


}

void Regist::getChectClick()
{

    if(!checkEdit())
    {
        getCheck->setText(QStringLiteral("获取"));
        getCheck->stop();
        getCheck->setEnabled(true);
        return;
    }
    //处理http
    QJsonObject jsonObj;
    jsonObj["email"]=email->text();
    QString url="http://127.0.0.1/get_verifycode";
    std::shared_ptr<HttpMgr> httpMgr=HttpMgr::getInstance();
    httpMgr->PostHttpReq(url,jsonObj,ReqId::ID_GET_VERIFY_CODE,Modules::REGISTERMOD);


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
    qDebug()<<"----regist";
    _handlers[id](jsonObj);
    return;
}

void Regist::yesButtonClick()
{
    if(!checkEdit())return;
    QJsonObject obj;
    obj["user"]=user->text();
    obj["email"]=email->text();
    obj["passwd"]=pw->text();
    obj["verifycode"]=check->text();
    qDebug()<<"-----";
    HttpMgr::getInstance()->PostHttpReq(gate_url_prefix+"/user_register",
                                        obj,ReqId::ID_REG_USER,Modules::REGISTERMOD);
}
