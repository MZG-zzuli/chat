#include "clickedlabel.h"
#include<QDebug>
ClickedLabel::ClickedLabel(QWidget* parent):QLabel(parent)
{
    setMinimumSize(25,25);
}

ClickedLabel::~ClickedLabel()
{
    qDebug()<<"xglabel\n\n";
}

void ClickedLabel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {
        if(GetCurState()==ClickLbState::Normal)
        {
            _curstate=ClickLbState::Selected;
            setProperty("state",_selected_hover);
        }else
        {
            _curstate=ClickLbState::Normal;
            setProperty("state",_normal_hover);

        }
        repolish(this);
        update();
        emit clicked();
    }
    QLabel::mousePressEvent(ev);
}

void ClickedLabel::enterEvent(QEvent *event)
{
    if(GetCurState()==ClickLbState::Normal)
    {
        setProperty("state",_normal_hover);
    }else
    {
        setProperty("state",_selected_hover);
    }
    repolish(this);
    update();
    QLabel::enterEvent(event);
}

void ClickedLabel::leaveEvent(QEvent *event)
{
    if(GetCurState()==ClickLbState::Normal)
    {
        setProperty("state",_normal);
    }else
    {
        setProperty("state",_selected);
    }
    repolish(this);
    update();
    QLabel::leaveEvent(event);
}

void ClickedLabel::SetState(QString normal, QString hover,  QString select, QString select_hover)
{
    _normal=normal;
    _normal_hover=hover;
    _selected=select;
    _selected_hover=select_hover;
    setProperty("state",_normal);
    repolish(this);
    update();
}

ClickLbState ClickedLabel::GetCurState()
{
    return _curstate;
}
