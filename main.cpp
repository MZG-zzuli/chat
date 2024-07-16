#include<QApplication>
#include<login.h>
#include<regist.h>
#include<mainwindow.h>
#include<QStyle>
#include<QFile>
#include<QDebug>
#include"registsuccess.h"
int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    QFile qss(":/style.qss");
    qss.open(QFile::ReadOnly);
    QString style=qss.readAll();
    qDebug()<<style;
    app.setStyleSheet(style);

    MainWindow* mainWindow=new MainWindow;
    mainWindow->show();

    return app.exec();

}
