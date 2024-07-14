#ifndef TIMERBTN_H
#define TIMERBTN_H

#include<QPushButton>
#include<QTimer>
#include<QMouseEvent>
class TimerBtn:public QPushButton
{
    Q_OBJECT
public:
    TimerBtn(QString _text="",QWidget* parent=nullptr);
    void stop();
private:
    virtual void mouseReleaseEvent(QMouseEvent* event);
    QTimer* timer=nullptr;
    int _counter;
    QString text;
};

#endif // TIMERBTN_H
