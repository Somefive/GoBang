
#include "GameMessageBox.h"
#include "mypainter.h"
#include "gameviewpanel.h"

#include <QDebug>

GameMessageBox::GameMessageBox(QWidget *_widget,const QString& _title,const QString& _content,const QString& _leftText,const QString& _rightText):
    GameViewPanel(_widget),Title(_title),Content(_content)
{
    QRect rect  = _widget->rect();
    this->setGeometry(rect.width()/4,rect.height()/4,rect.width()/2,rect.height()/3);

    titleLabel = new QLabel(Title,this);
    contentLabel = new QLabel(Content,this);

    leftButton = new GameButton(_leftText,this);
    rightButton = new GameButton(_rightText,this);
    centralButton = NULL;

    Initialize();

    connect(leftButton,SIGNAL(Clicked()),this,SLOT(leftButtonClicked()));
    connect(rightButton,SIGNAL(Clicked()),this,SLOT(rightButtonClicked()));
}

GameMessageBox::GameMessageBox(QWidget *_widget, const QString &_title, const QString &_content, const QString &_centralText):
    GameViewPanel(_widget),Title(_title),Content(_content)
{
    QRect rect  = _widget->rect();
    this->setGeometry(rect.width()/4,rect.height()/4,rect.width()/2,rect.height()/3);

    titleLabel = new QLabel(Title,this);
    contentLabel = new QLabel(Content,this);

    leftButton = NULL;
    rightButton = NULL;
    centralButton = new GameButton(_centralText,this);

    Initialize();

    connect(centralButton,SIGNAL(Clicked()),this,SLOT(centralButtonClicked()));
}

GameMessageBox::GameMessageBox(QWidget *_widget, const QString &_title, const QString &_content):
    GameViewPanel(_widget),Title(_title),Content(_content)
{
    QRect rect  = _widget->rect();
    this->setGeometry(rect.width()/4,rect.height()/4,rect.width()/2,rect.height()/3);

    titleLabel = new QLabel(Title,this);
    contentLabel = new QLabel(Content,this);

    leftButton = NULL;
    rightButton = NULL;
    centralButton = NULL;

    Initialize();

}

void GameMessageBox::Initialize()
{
    titleLabel->setFont(QFont("Lucida Bright",20));
    contentLabel->setFont(QFont("Lucida Bright",16));
    titleLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    contentLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::white);
    contentLabel->setPalette(palette);
    palette.setColor(QPalette::WindowText,Qt::yellow);
    titleLabel->setPalette(palette);

    contentLabel->setWordWrap(true);
}

void GameMessageBox::paintEvent(QPaintEvent *event)
{
    GameViewPanel::paintEvent(event);

    int _w = this->width(), _h=this->height();

    titleLabel->setGeometry(0,_h*0.05,_w,_h*0.23);
    contentLabel->setGeometry(0,_h*0.3,_w,_h*0.48);
    if(leftButton!=NULL && rightButton!=NULL)
    {
        leftButton->setGeometry(_w/6,_h*0.8,_w/4,_h*0.12);
        rightButton->setGeometry(_w*7/12,_h*0.8,_w/4,_h*0.12);
    }
    else if(centralButton!=NULL)
        centralButton->setGeometry(_w*3/8,_h*0.8,_w/4,_h*0.12);
    else
    {
        titleLabel->setGeometry(0,_h*0.2,_w,_h*0.23);
        contentLabel->setGeometry(0,_h*45,_w,_h*0.53);
    }
}

void GameMessageBox::leftButtonClicked()
{
    emit LeftButtonClicked();
}

void GameMessageBox::rightButtonClicked()
{
    emit RightButtonClicked();
}

void GameMessageBox::centralButtonClicked()
{
    emit CentralButtonClicked();
}
