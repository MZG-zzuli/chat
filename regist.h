#ifndef REGIST_H
#define REGIST_H
#include<QWidget>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QStyle>
#include<QDebug>
class Regist : public QWidget
{
    Q_OBJECT
public:
    explicit Regist(QWidget *parent = nullptr);
private:
    QLabel* err_tip=nullptr;
    QLineEdit* user=nullptr;
    QLineEdit* email=nullptr;
    QLineEdit* pw=nullptr;
    QLineEdit* pw2=nullptr;
    QLineEdit* check=nullptr;
    void changeErrtip(QString message);
private slots:
    void getChectClick();
signals:
    void noToLogin();

};

#endif // REGIST_H
