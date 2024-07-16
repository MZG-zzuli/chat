#include "resetpwd.h"

ResetPwd::ResetPwd(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* mainLayout=new QVBoxLayout;
    setLayout(mainLayout);
    mainLayout->addStretch(1);
    err_tip=new QLabel("");
    err_tip->setObjectName("err_tip");
    QHBoxLayout* errLayout=new QHBoxLayout;
    errLayout->setAlignment(Qt::AlignCenter);
    errLayout->addWidget(err_tip);
    mainLayout->addLayout(errLayout);
    QLabel* nameLabel=new QLabel(QStringLiteral("用户名:"));
    name=new QLineEdit;
    QHBoxLayout* nameLayout=new QHBoxLayout;
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(name);
    mainLayout->addLayout(nameLayout);
    QLabel* emailLabel=new QLabel(QStringLiteral("邮  箱:"));
    email=new QLineEdit;
    QHBoxLayout* emailLayout=new QHBoxLayout;
    emailLayout->addWidget(emailLabel);
    emailLayout->addWidget(email);
    mainLayout->addLayout(emailLayout);

    QLabel* verifycodeLabel=new QLabel(QStringLiteral("验证码:"));
    verifycode=new QLineEdit;
    getVerify=new TimerBtn(QStringLiteral("获取"));
    connect(getVerify,&TimerBtn::clicked,this,&ResetPwd::getVerifyCode);

    QHBoxLayout* verifyLayout=new QHBoxLayout;
    verifyLayout->addWidget(verifycodeLabel);
    verifyLayout->addWidget(verifycode);
    verifyLayout->addWidget(getVerify);
    mainLayout->addLayout(verifyLayout);

    QLabel* newpwdLabel=new QLabel(QStringLiteral("新密码:"));
    newpwd=new QLineEdit;
    newpwd->setEchoMode(QLineEdit::Password);
    ClickedLabel* pwdSelect=new ClickedLabel;
    connect(pwdSelect,&ClickedLabel::clicked,this,[=](){
        if(pwdSelect->GetCurState()==ClickLbState::Normal)
        {
            newpwd->setEchoMode(QLineEdit::Password);
        }else
        {
            newpwd->setEchoMode(QLineEdit::Normal);
        }
    });
    pwdSelect->setObjectName("pwvis");
    pwdSelect->SetState("unvisible","unvisible_hover","visible",
                          "visible_hover");
    QHBoxLayout* pwdLayout=new QHBoxLayout;
    pwdLayout->addWidget(newpwdLabel);
    pwdLayout->addWidget(newpwd);
    pwdLayout->addWidget(pwdSelect);
    mainLayout->addLayout(pwdLayout);

    mainLayout->addStretch(1);
    QHBoxLayout* yesOrNoLayout=new QHBoxLayout;
    QPushButton* yes=new QPushButton(QStringLiteral("确认"));
    connect(yes,&QPushButton::clicked,this,&ResetPwd::on_sure_btn_clicked);
    QPushButton* no=new QPushButton(QStringLiteral("返回"));
    connect(no,&QPushButton::clicked,this,[this](){
        qDebug()<<"return login";
        emit toLogin();
    });
    yesOrNoLayout->addWidget(yes);
    yesOrNoLayout->addWidget(no);
    mainLayout->addLayout(yesOrNoLayout);

    mainLayout->addStretch(1);

    initHandlers();
    connect(HttpMgr::getInstance().get(),&HttpMgr::sig_reset_mod_finish,this,&ResetPwd::slot_reset_mod_finish);
}

void ResetPwd::showTip(const QString &str, bool b_ok)
{
    err_tip->setText(str);
    if(b_ok)
    {
        err_tip->setProperty("state","normal");
    }else{
        err_tip->setProperty("state","err");
    }
    err_tip->setText(str);
    repolish(err_tip);
}

void ResetPwd::initHandlers()
{
    _handlers.insert(ReqId::ID_GET_VERIFY_CODE,[this](QJsonObject& obj){
        int error=obj["error"].toInt();
        if(error!=ErrorCodes::SUCCESS)
        {
            showTip(QStringLiteral("网络错误"),false);
            return;
        }
//        QString email=obj[QString("email")].toString();
        showTip(QStringLiteral("验证码已发送，注意查收"),true);
//        qDebug()<<"emailCode:"<<email;
        return;
    });
    _handlers.insert(ReqId::ID_RESET_PWD,[this](QJsonObject& obj){
        qDebug()<<"-----------======ID_RESET_PWD=====-------";
        int error=obj["error"].toInt();
        if(error!=ErrorCodes::SUCCESS)
        {
            showTip(QStringLiteral("重置失败"),false);
            return;
        }
        showTip(QStringLiteral("重置成功"),true);
        return;
    });
}

bool ResetPwd::checkUserValid()
{
    if(name->text()=="")
    {
        showTip(QStringLiteral("用户名不能为空"),false);
        return false;
    }
    return true;
}

bool ResetPwd::checkPassValid()
{
    QString passwd=newpwd->text();
    if(passwd.length()<6||passwd.length()>15)
    {
        showTip(QStringLiteral("密码长度应为6~15"),false);
        return false;
    }
    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match = regExp.match(passwd).hasMatch();
    if(!match){
        //提示字符非法
        showTip(QStringLiteral("不能包含非法字符"),false);
        return false;;
    }
    return true;
}

bool ResetPwd::checkEmailValid()
{
    auto email_ = email->text();
    // 邮箱地址的正则表达式
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email_).hasMatch(); // 执行正则表达式匹配
    if(!match){
        //提示邮箱不正确
        showTip(QStringLiteral("邮箱地址不正确"),false);
        return false;
    }
    return true;
}

void ResetPwd::getVerifyCode()
{
    if(!checkUserValid()||!checkEmailValid())
    {
        return;
    }
    QJsonObject obj;
    obj["email"]=email->text();
    HttpMgr::getInstance()->PostHttpReq(gate_url_prefix+"/get_verifycode",obj,ReqId::ID_GET_VERIFY_CODE,Modules::RESETMOD);

}

void ResetPwd::on_sure_btn_clicked()
{
    if(!checkUserValid()||!checkEmailValid()||!checkPassValid())
    {
        return;
    }
    QJsonObject obj;
    obj["email"]=email->text();
    obj["name"]=name->text();
    obj["verifycode"]=verifycode->text();
    obj["newpwd"]=newpwd->text();
    HttpMgr::getInstance()->PostHttpReq(gate_url_prefix+"/reset_pwd",obj,ReqId::ID_RESET_PWD,Modules::RESETMOD);
    qDebug()<<"reset pwd ok";
}

void ResetPwd::slot_reset_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    qDebug()<<"resetpwd or getverifycode ok---------";
    if(err!=ErrorCodes::SUCCESS)
    {
        showTip(QStringLiteral("网络错误"),false);
        return;
    }
    QJsonDocument doc=QJsonDocument::fromJson(res.toUtf8());
    QJsonObject obj=doc.object();

    _handlers[id](obj);
    qDebug()<<"resetpwd or getverifycode ok";
}
