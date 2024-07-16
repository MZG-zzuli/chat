#ifndef REGISTSUCCESS_H
#define REGISTSUCCESS_H

#include <QWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QTimer>
class RegistSuccess : public QWidget
{
    Q_OBJECT
public:
    explicit RegistSuccess(QWidget *parent = nullptr);
    void start();
private:
    QLabel* lab=nullptr;
    int time;
    QTimer* timer=nullptr;
signals:
    void toLogin();
};

#endif // REGISTSUCCESS_H
