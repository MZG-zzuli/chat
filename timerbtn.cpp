#include "timerbtn.h"

TimerBtn::TimerBtn(QString _text,QWidget *parent):QPushButton(parent),text(_text),_counter(10)
{
    setText(text);
    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,[&](){
        _counter--;
        if(_counter<=0)
        {
            this->_counter=10;
            setEnabled(true);
            setText(text);
            timer->stop();
            return;
        }
        this->setText(QString::number(_counter));

    });

}

void TimerBtn::stop()
{
    _counter=10;
    this->timer->stop();
}

void TimerBtn::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        this->setEnabled(false);
        this->setText(QString::number(_counter));

        timer->start(1000);
        emit clicked();
    }
    QPushButton::mouseReleaseEvent(event);
}
