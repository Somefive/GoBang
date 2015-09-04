#include "GameTypeBox.h"
#include <QKeyEvent>


void GameTypeBox::paintEvent(QPaintEvent *event)
{
    GameViewPanel::paintEvent(event);
    int w = this->width(), h = this->height();
    editBox->setGeometry(w*0.05,h*0.1,w*0.9,h*0.8);
    editBox->setText(text);
}

void GameTypeBox::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Return:
        emit EmitText(text);
        text.clear();
        break;
    case Qt::Key_Backspace:
        if(text.size()>=1)
            text.remove(text.size()-1,1);
    case Qt::Key_Ampersand:
    case Qt::Key_Percent:
        break;
    default:
        text += event->text();
        break;
    }
    if(text.size()>MaxTypeLength)
        text.remove(MaxTypeLength-1,text.size()-MaxTypeLength);
    update();
}

GameTypeBox::GameTypeBox(QWidget* parent):
    GameViewPanel(parent),MaxTypeLength(15)
{
    int w = parent->width(), h = parent->height();
    this->setGeometry(w*0.15,h*0.9,w*0.7,h*0.05);
    editBox = new QLabel(this);
    editBox->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    QPalette palette;
    palette.setBrush(QPalette::Foreground,Qt::white);
    palette.setBrush(QPalette::HighlightedText,Qt::yellow);
    palette.setBrush(QPalette::Highlight,Qt::gray);
    editBox->setPalette(palette);
    editBox->setFont(QFont("Comic Sans MS",10));

    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();
}

