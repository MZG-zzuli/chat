#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStackedWidget>
#include<QVBoxLayout>
#include<login.h>
#include<regist.h>
#include<QDebug>
#include"registsuccess.h"
#include"resetpwd.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:
private:
    Login* loginWindow=nullptr;
    Regist* registWindow=nullptr;
    RegistSuccess* registSuccessWindow=nullptr;
    ResetPwd* resetPwdWindow=nullptr;

};

#endif // MAINWINDOW_H
