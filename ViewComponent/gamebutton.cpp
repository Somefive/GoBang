#include "gamebutton.h"
#include "mypainter.h"

GameButton::GameButton(const QString &_text, QWidget *_parent):
    Text(_text),QWidget(_parent),RoundedRim(true)
{
    setColor(Qt::white,Qt::black,GameButton::NORMAL);
    setColor(Qt::black,Qt::gray,GameButton::PRESSED);
    setColor(Qt::white,Qt::gray,GameButton::ENTERED);

    label = new QLabel(this);
    label->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);

    textColor = textColorNormal;
    backColor = backColorNormal;

    setFontSize(12);

}

void GameButton::paintEvent(QPaintEvent *)
{
    int _r = 0.05*(this->width()+this->height());
    MyPainter painter(this);
    backColor.setAlpha(200);
    painter.setBrush(QBrush(backColor));
    if(RoundedRim)
        painter.drawRoundedRect(this->rect(),_r,_r);
    else
        painter.drawRect(this->rect());

    label->setGeometry(this->rect());
    label->setText(Text);
    QPalette palette;
    palette.setColor(QPalette::WindowText,textColor);
    label->setPalette(palette);
    label->update();
}

void GameButton::setColor(const QColor &_textColor, const QColor &_backColor, GameButton::GBSTATE _state)
{
    switch(_state)
    {
    case GameButton::NORMAL:
        textColorNormal = _textColor;
        backColorNormal = _backColor;
        break;
    case GameButton::PRESSED:
        textColorPressed = _textColor;
        backColorPressed = _backColor;
        break;
    case GameButton::ENTERED:
        textColorEntered = _textColor;
        backColorEntered = _backColor;
        break;
    default:
        break;
    }
}

void GameButton::enterEvent(QEvent *)
{
    textColor = textColorEntered;
    backColor = backColorEntered;
    update();
}

void GameButton::leaveEvent(QEvent *)
{
    textColor = textColorNormal;
    backColor = backColorNormal;
    update();
}

void GameButton::mousePressEvent(QMouseEvent *)
{
    textColor = textColorPressed;
    backColor = backColorPressed;
    update();
}

void GameButton::mouseReleaseEvent(QMouseEvent *)
{
    textColor = textColorNormal;
    backColor = backColorPressed;
    update();
    emit Clicked();
    emit Clicked(this);
}

void GameButton::setFontSize(int px)
{
    label->setFont(QFont("Maiandra GD",px));
}

int GameButton::getFontSize()
{
    return label->font().pointSize();
}

void GameButton::setText(const QString &_text)
{
    Text = _text;
}

void GameButton::setRimShape(bool Rounded)
{
    RoundedRim = Rounded;
}
