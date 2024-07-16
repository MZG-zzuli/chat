#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    setMaximumSize(250,400);
    QStackedWidget* mainWidget=new QStackedWidget(this);
    setCentralWidget(mainWidget);

    loginWindow=new Login(this);
    registWindow=new Regist(this);
    registSuccessWindow=new RegistSuccess(this);
    resetPwdWindow=new ResetPwd(this);
    mainWidget->addWidget(loginWindow);
    mainWidget->addWidget(registWindow);
    mainWidget->addWidget(registSuccessWindow);
    mainWidget->addWidget(resetPwdWindow);
    connect(loginWindow,&Login::toRegist,this,[=]{
        qDebug()<<"---";
        //mainWidget->setCurrentWidget(loginWindow);
        mainWidget->setCurrentIndex(1);
    });
    connect(loginWindow,&Login::toResetPwd,[=](){
        mainWidget->setCurrentWidget(resetPwdWindow);
    });
    connect(registWindow,&Regist::noToLogin,this,[=]{
        qDebug()<<"---";
        //mainWidget->setCurrentWidget(registWindow);
        mainWidget->setCurrentIndex(0);
    });
    connect(registWindow,&Regist::registOk,this,[=]{
        mainWidget->setCurrentWidget(registSuccessWindow);
        registSuccessWindow->start();
    });
    connect(registSuccessWindow,&RegistSuccess::toLogin,this,[=]{
        mainWidget->setCurrentIndex(0);
    });
    connect(resetPwdWindow,&ResetPwd::toLogin,this,[=](){
        qDebug()<<"reset tologin";
        mainWidget->setCurrentWidget(loginWindow);
    });
}
