#include "gamemenuinterface.h"
#include "mypainter.h"
#include <QDebug>
#include <QCoreApplication>

GameMenuInterface::GameMenuInterface(QWidget *_parent):
    GameViewPanel(_parent)
{
    MuteRightButton = true;
    Fixed = true;
    this->setGeometry(_parent->rect());
    Title = new QLabel("Flow Free",this);
    Author = new QLabel("via Somefive",this);
    Five = new GameSizeChangeButton("5×5",this);
    Six = new GameSizeChangeButton("6×6",this);
    Seven = new GameSizeChangeButton("7×7",this);
    Addition = new GameSizeChangeButton("Addition",this);
    backImage = new QImage(QCoreApplication::applicationDirPath()+"/Resources/Image/back.jpg");
    InitializeComponent();
}

void GameMenuInterface::InitializeComponent()
{
    int _w = this->width(), _h = this->height();
    Title->setGeometry(_w*0.2,_h*0.08,_w*0.6,_h*0.2);
    Author->setGeometry(_w*0.7,_h*0.92,_w*0.25,_h*0.05);
    Five->setGeometry(_w*0.35,_h*0.4,_w*0.3,_h*0.08);
    Six->setGeometry(_w*0.35,_h*0.52,_w*0.3,_h*0.08);
    Seven->setGeometry(_w*0.35,_h*0.64,_w*0.3,_h*0.08);
    Addition->setGeometry(_w*0.35,_h*0.76,_w*0.3,_h*0.08);

    ButtonInitialize(Five);
    ButtonInitialize(Six);
    ButtonInitialize(Seven);
    ButtonInitialize(Addition);

    Title->setFont(QFont("Lucida Handwriting",48));
    Author->setFont(QFont("Segoe Script",14));
    QPalette palette;
    palette.setBrush(QPalette::WindowText,Qt::white);
    Title->setPalette(palette);
    palette.setBrush(QPalette::WindowText,Qt::gray);
    Author->setPalette(palette);
    backImage->scaled(_w,_h);

    connect(Five,SIGNAL(Clicked()),this,SLOT(ChooseFive()));
    connect(Six,SIGNAL(Clicked()),this,SLOT(ChooseSix()));
    connect(Seven,SIGNAL(Clicked()),this,SLOT(ChooseSeven()));
    connect(Addition,SIGNAL(Clicked()),this,SLOT(ChooseAddition()));
}

void GameMenuInterface::ButtonInitialize(GameSizeChangeButton *button)
{
    button->setFontSize(18);
    button->setRatio(1.25,1.25);
    button->setSizeIncrement(this->width()*0.3,this->height()*0.08);
}

void GameMenuInterface::paintEvent(QPaintEvent *event)
{
    this->setGeometry(this->parentWidget()->rect());
    int _w = this->width(), _h = this->height();
    Title->setGeometry(_w*0.2,_h*0.08,_w*0.6,_h*0.2);
    Author->setGeometry(_w*0.7,_h*0.92,_w*0.25,_h*0.05);
    Five->setGeometry(_w*0.35,_h*0.4,_w*0.3,_h*0.08);
    Six->setGeometry(_w*0.35,_h*0.52,_w*0.3,_h*0.08);
    Seven->setGeometry(_w*0.35,_h*0.64,_w*0.3,_h*0.08);
    Addition->setGeometry(_w*0.35,_h*0.76,_w*0.3,_h*0.08);
    MyPainter painter(this) ;
    painter.drawImage(this->rect(),*backImage);
    GameViewPanel::paintEvent(event);
}

void GameMenuInterface::ChooseFive()
{
    emit StartGame(5,1);
}

void GameMenuInterface::ChooseSix()
{
    emit StartGame(6,1);
}

void GameMenuInterface::ChooseSeven()
{
    emit StartGame(7,1);
}

void GameMenuInterface::ChooseAddition()
{
    emit ChooseLevelMenu();
}

