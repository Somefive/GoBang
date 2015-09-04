#include "gamelevelchooser.h"
#include <QCoreApplication>

#include "mypainter.h"
#include <QDebug>

GameLevelChooser::GameLevelChooser(QWidget *parent):
    GameViewPanel(parent)
{
    this->Fixed = true;

    backImage = new QImage(QCoreApplication::applicationDirPath()+"/Resources/Image/back.jpg");

    Title = new QLabel("Game Chooser",this);
    levelLabel = new QLabel("Game Size",this);
    gameNoLabel = new QLabel("Game Number",this);
    confirmButton = new GameButton("Start",this);
    menuButton = new GameButton("Menu",this);
    levelList = new QStringList();
    numList = new QStringList();

    for(int i=5;i<=14;++i)
    {
        QString level = QString::number(i) + "×" + QString::number(i);
        levelList->push_back(level);
    }
    for(int i=1;i<=30;++i)
    {
        QString num = QString::number(i);
        numList->push_back(num);
    }
    levelChooser = new GameChooseBox(this,5);
    gameNoChooser = new GameChooseBox(this,5);
    levelChooser->setChoicesSource(levelList);
    gameNoChooser->setChoicesSource(numList);
    InitializeComponent();

    levelChooser->setFontSize(16);
    gameNoChooser->setFontSize(16);

    confirmButton->setFontSize(16);
    menuButton->setFontSize(16);

    this->setGeometry(parent->rect());

    backImage->scaled(this->size());

    connect(confirmButton,SIGNAL(Clicked()),this,SLOT(ConfirmButtonPressed()));
    connect(menuButton,SIGNAL(Clicked()),this,SLOT(MenuButtonPressed()));

}

void GameLevelChooser::InitializeComponent()
{
    QPalette palette;
    Title->setFont(QFont("Lucida Handwriting",30));
    palette.setBrush(QPalette::WindowText,Qt::white);
    Title->setPalette(palette);
    levelLabel->setFont(QFont("Maiandra GD",18));
    gameNoLabel->setFont(QFont("Maiandra GD",18));
    levelLabel->setPalette(palette);
    Title->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    levelLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    gameNoLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    gameNoLabel->setPalette(palette);

}

void GameLevelChooser::paintEvent(QPaintEvent *event)
{
    this->setGeometry(parent->rect());
    MyPainter painter(this);
    painter.drawImage(this->rect(),*backImage);
    QColor bgcolor(Qt::white);
    bgcolor.setAlpha(200);
    painter.fillRect(this->rect(),bgcolor);

    int _h = this->height(), _w = this->width();
    Title->setGeometry(_w*0.2,_h*0.05,_w*0.6,_h*0.2);
    levelLabel->setGeometry(_w*0.15,_h*0.3,_w*0.35,_h*0.1);
    gameNoLabel->setGeometry(_w*0.55,_h*0.3,_w*0.35,_h*0.1);
    levelChooser->setGeometry(_w*0.15,_h*0.45,_w*0.35,_h*0.35);
    gameNoChooser->setGeometry(_w*0.55,_h*0.45,_w*0.35,_h*0.35);
    confirmButton->setGeometry(_w*0.55,_h*0.85,_w*0.35,_h*0.07);
    menuButton->setGeometry(_w*0.15,_h*0.85,_w*0.35,_h*0.07);

    GameViewPanel::paintEvent(event);
}

void GameLevelChooser::MenuButtonPressed()
{
    emit BackToMenu();
}

void GameLevelChooser::ConfirmButtonPressed()
{
    int _level=5, _gameNo = 1;
    QStringList levelText = levelChooser->Value().split("×");
    _level = levelText.at(0).toInt();
    _gameNo = gameNoChooser->Value().toInt();
    emit StartGame(_level,_gameNo);
}
