#include "gamesizechangebutton.h"

GameSizeChangeButton::GameSizeChangeButton(const QString &_text, QWidget *_parent):
    GameButton(_text,_parent)
{
    setRatio(1.5,1.5);
    setAlignment(GameSizeChangeButton::XCenter|GameSizeChangeButton::YCenter);
}

void GameSizeChangeButton::setRatio(double _x, double _y)
{
    xRatio = _x;
    yRatio = _y;
}

void GameSizeChangeButton::setAlignment(Alignment _alignment)
{
    if(_alignment>0)
        alignment |= _alignment;
    else
        alignment &= _alignment;
}

void GameSizeChangeButton::enterEvent(QEvent *event)
{
    int _w = this->width(), _h = this->height();
    OriginalRect = QRect(this->pos().x(),this->pos().y(),_w,_h);
    OriginalPointSize = getFontSize();
    setFontSize(OriginalPointSize*yRatio);
    int dx = 0, dy = 0;
    if((alignment&XCenter)!=0)
        dx = (_w-_w*xRatio)/2;
    if((alignment&YCenter)!=0)
        dy = (_h-_h*yRatio)/2;
    this->setGeometry(QRect(OriginalRect.x()+dx,OriginalRect.y()+dy,_w*xRatio,_h*yRatio));
    GameButton::enterEvent(event);
}

void GameSizeChangeButton::leaveEvent(QEvent *event)
{
    setFontSize(OriginalPointSize);
    this->setGeometry(OriginalRect);
    GameButton::leaveEvent(event);
}
