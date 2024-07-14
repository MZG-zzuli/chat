#ifndef CLICKEDLABEL_H
#define CLICKEDLABEL_H

#include <QLabel>
#include<QMouseEvent>
#include<global.h>
class ClickedLabel:public QLabel
{
    Q_OBJECT
public:
    ClickedLabel(QWidget* parent=nullptr);
    ~ClickedLabel();
    virtual void mousePressEvent(QMouseEvent *ev) override;
    virtual void enterEvent(QEvent* event) override;
    virtual void leaveEvent(QEvent* event) override;
    void SetState(QString normal="", QString hover="",
                  QString select="", QString select_hover="");
    ClickLbState GetCurState();
protected:
private:
    QString _normal;
    QString _normal_hover;
    QString _selected;
    QString _selected_hover;
    ClickLbState _curstate;
signals:
    void clicked(void);
};

#endif // CLICKEDLABEL_H
