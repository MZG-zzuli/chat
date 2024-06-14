#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    setMaximumSize(250,400);
    QStackedWidget* mainWidget=new QStackedWidget;
    setCentralWidget(mainWidget);

    loginWindow=new Login;
    registWindow=new Regist;
    mainWidget->addWidget(loginWindow);
    mainWidget->addWidget(registWindow);
    connect(loginWindow,&Login::toRegist,this,[=]{
        qDebug()<<"---";
        //mainWidget->setCurrentWidget(loginWindow);
        mainWidget->setCurrentIndex(1);
    });
    connect(registWindow,&Regist::noToLogin,this,[=]{
        qDebug()<<"---";
        //mainWidget->setCurrentWidget(registWindow);
        mainWidget->setCurrentIndex(0);
    });
}
