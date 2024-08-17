#include "login.h"
#include"tcpmgr.h"
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
    nameLayout->addWidget(new QLabel(QStringLiteral("邮箱:")));
    email=new QLineEdit(this);
    nameLayout->addWidget(email);
    mainLayout->addLayout(nameLayout);

    QHBoxLayout* pwLayout=new QHBoxLayout;
    pwLayout->addWidget(new QLabel(QStringLiteral("密码:")));
    pw=new QLineEdit(this);
    pw->setEchoMode(QLineEdit::Password);
    pwLayout->addWidget(pw);
    mainLayout->addLayout(pwLayout);

    QHBoxLayout* forgetLayout=new QHBoxLayout;
    forgetLayout->setAlignment(Qt::AlignRight);
    ClickedLabel* forget_label=new ClickedLabel(this);
    connect(forget_label,&ClickedLabel::clicked,this,[this](){
        emit toResetPwd();
    });
    forget_label->setText(QStringLiteral("忘记密码"));
    forget_label->setObjectName("forget_label");
    forget_label->SetState("normal","hover","selected","selected_hover");
    forgetLayout->addWidget(forget_label);
    mainLayout->addLayout(forgetLayout);

    QPushButton* loginButton=new QPushButton(QStringLiteral("登录"),this);
    connect(loginButton,&QPushButton::clicked,this,&Login::loginClick);
    mainLayout->addWidget(loginButton);

    QPushButton* registButton=new QPushButton(QStringLiteral("注册"),this);
    mainLayout->addWidget(registButton);
    //connect(registButton,SIGNAL(clicked(bool)),this,SLOT(registHandle()));
    connect(registButton,&QPushButton::clicked,this,[=]{
        emit toRegist();
    });
    connect(HttpMgr::getInstance().get(),&HttpMgr::sig_login_mod_finish,this,&Login::slot_login_mod_finish);
    initHttpHandlers();

    connect(this,&Login::sig_connect_tcp,TcpMgr::getInstance().get(),TcpMgr::slot_tcp_connect);
    connect(TcpMgr::getInstance().get(),&TcpMgr::sig_con_success,this,Login::slot_tcp_con_finish);
}

Login::~Login()
{
    qDebug()<<"===";
}

void Login::registHandle()
{
    emit toRegist();
}

void Login::loginClick()
{
    QString email_=email->text();
    QString pw_=pw->text();
    QJsonObject obj;;
    obj["email"]=email_;
    obj["passwd"]=pw_;
    std::shared_ptr<HttpMgr> http=HttpMgr::getInstance();
    http->PostHttpReq(gate_url_prefix+"/user_login",obj,ReqId::ID_LOGIN_USER,Modules::LOGINMOD);



}

void Login::slot_login_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err!=ErrorCodes::SUCCESS)
    {
        qDebug()<<"network error!!!";
    }
    QJsonDocument doc=QJsonDocument::fromJson(res.toUtf8());
    if(doc.isNull())
    {
        qDebug()<<"json error";
    }
    qDebug()<<"---"<<id;
    _handlers[id](doc.object());


}

void Login::slot_tcp_con_finish(bool bsuccess)
{
    if(bsuccess)
    {
        QJsonObject jsonObj;
        jsonObj["uid"]=uid_;
        jsonObj["token"]=token_;
        QJsonDocument doc(jsonObj);
        QString jsonString=doc.toJson(QJsonDocument::Indented);
        TcpMgr::getInstance()->sig_send_data(ReqId::ID_CHAT_LOGIN,jsonString);
    }else
    {
        qDebug()<<"网络异常";


    }
}

void Login::initHttpHandlers()
{
    _handlers.insert(ReqId::ID_LOGIN_USER,[this](QJsonObject obj){
        qDebug()<<"=========";
        if(obj["error"].toInt()!=ErrorCodes::SUCCESS)
        {
            qDebug()<<"参数错误";
        }
        qDebug()<<obj["email"]<<"login success";
        qDebug()<<obj["host"]<<":"<<obj["port"];

        ServerInfo serverInfo;
        serverInfo.Uid=obj["uid"].toInt();
        serverInfo.Host=obj["host"].toString();
        serverInfo.Port=obj["port"].toString();
        serverInfo.Token=obj["token"].toString();
        uid_=serverInfo.Uid;
        token_=serverInfo.Token;
        emit sig_connect_tcp(serverInfo);

    });
}
