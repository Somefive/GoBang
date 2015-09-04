#include "ViewComponent/gameviewpanel.h"
#include "mypainter.h"
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>

GameViewPanel::GameViewPanel(QWidget *_widget):
    QWidget(_widget),Moving(false),parent(_widget),Fixed(false),RightButtonPressed(false),MuteRightButton(false)
{
    QRect rect  = _widget->rect();
    this->setGeometry(rect.width()/4,rect.height()/4,rect.width()/2,rect.height()/2);
    setColor(Qt::black);
    this->setFocusPolicy(Qt::StrongFocus);
}

void GameViewPanel::paintEvent(QPaintEvent *)
{
    MyPainter painter(this);
    backColor.setAlpha(200);
    painter.setBrush(QBrush(backColor));
    int _r = (this->height()+this->width())*0.05;
    if(!Fixed)
        painter.drawRoundedRect(this->rect(),_r,_r);
    else
        painter.drawRect(this->rect());
}

void GameViewPanel::setColor(const QColor &color)
{
    backColor = color;
}

void GameViewPanel::mousePressEvent(QMouseEvent *event)
{
    if((event->button()&Qt::RightButton)!=0)
        RightButtonPressed = true;
    if(!Fixed&&(event->button()&Qt::LeftButton)!=0)
    {
        LastCursorPosition = event->pos();
        if(LastCursorPosition.x()<=0 || LastCursorPosition.x()>=this->width())
            return;
        if(LastCursorPosition.y()<=0 || LastCursorPosition.y()>=this->height())
            return;
        LastWidgetPosition = this->pos();
        Moving = true;
    }
}

void GameViewPanel::mouseReleaseEvent(QMouseEvent *event)
{
    if(!MuteRightButton && (event->button()&Qt::LeftButton)!=0)
        Moving = false;
    if((event->button()&Qt::RightButton)!=0&&RightButtonPressed)
    {
        RightButtonPressed = false;
        setMoveState(Fixed);
    }
}

void GameViewPanel::mouseMoveEvent(QMouseEvent *event)
{
    if(Fixed)
        return;
    if(!Moving)
        return;
    QPoint posinparent = mapToParent(event->pos());
    if(posinparent.x()<=0||posinparent.x()>=parent->width()||
       posinparent.y()<=0||posinparent.y()>=parent->height())
    {
        Moving = false;
        return;
    }
    int dx = event->pos().x()-LastCursorPosition.x();
    int dy = event->pos().y()-LastCursorPosition.y();
    this->move(this->pos().x()+dx,this->pos().y()+dy);
    this->update();
}

void GameViewPanel::setMoveState(bool movable)
{
    Fixed = !movable;
    update();
}
