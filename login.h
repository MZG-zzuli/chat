#ifndef LOGIN_H
#define LOGIN_H

#include<QWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QDebug>
class Login:public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
public slots:
    void registHandle();
signals:
    //注册信号
    void toRegist();

};

#endif // LOGIN_H
