#include "gameinfoviewer.h"
#include "gameviewpanel.h"

GameInfoViewer::GameInfoViewer(QWidget *parent, GameSetting *_gameSetting):
    GameViewPanel(parent),gameSetting(_gameSetting)
{

    header = new QLabel(this);

    info = new QLabel(this);

    retryButton = new GameButton("Retry",this);
    backToMenuButton = new GameButton("Menu",this);
    nextButton = new GameButton("→",this);
    previosButton = new GameButton("←",this);
    answerButton = new GameButton("Answer",this);

    Initialize();

    connect(retryButton,SIGNAL(Clicked()),this,SLOT(RetryButtonClicked()));
    connect(backToMenuButton,SIGNAL(Clicked()),this,SLOT(BackToMenuButtonClicked()));
    connect(nextButton,SIGNAL(Clicked()),this,SLOT(NextButtonClicked()));
    connect(previosButton,SIGNAL(Clicked()),this,SLOT(PreviousButtonClicked()));
    connect(answerButton,SIGNAL(Clicked()),this,SLOT(AnswerButtonClicked()));

}

void GameInfoViewer::Initialize()
{
    QPalette palette;
    palette.setBrush(QPalette::WindowText,Qt::yellow);
    header->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    header->setPalette(palette);
    palette.setBrush(QPalette::WindowText,Qt::white);
    info->setPalette(palette);
    info->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);

    header->setWordWrap(true);
}

void GameInfoViewer::paintEvent(QPaintEvent *event)
{
    int _pw = parent->width(), _ph = parent->height();

    if(abs(this->width()-_pw*3/5)>10 || abs(this->height()-_ph/3)>10)
        this->setGeometry(_pw/5,_ph/3,_pw*3/5,_ph*1/3);

    GameViewPanel::paintEvent(event);

    UpdateText();

    header->setFont(QFont("Lucida Bright",24));
    info->setFont(QFont("Lucida Bright",16));

    int _w = this->width(), _h=this->height();

    header->setGeometry(_w*0.1,_h*0.1,_w*0.8,_h*0.15);
    info->setGeometry(_w*0.15,_h*0.25,_w*0.7,_h*0.5);
    retryButton->setGeometry(_w*0.15,_h*0.75,_w*0.25,_h*0.1);
    backToMenuButton->setGeometry(_w*0.6,_h*0.75,_w*0.25,_h*0.1);
    previosButton->setGeometry(_w*0.15,_h*0.88,_w*0.1,_h*0.1);
    nextButton->setGeometry(_w*0.3,_h*0.88,_w*0.1,_h*0.1);
    answerButton->setGeometry(_w*0.6,_h*0.88,_w*0.25,_h*0.1);
}

void GameInfoViewer::RetryButtonClicked()
{
    emit Retry();
}

void GameInfoViewer::BackToMenuButtonClicked()
{
    emit BackToMenu();
}

void GameInfoViewer::NextButtonClicked()
{
    emit NextGame();
}

void GameInfoViewer::PreviousButtonClicked()
{
    emit PreviousGame();
}

void GameInfoViewer::AnswerButtonClicked()
{
    emit AnswerGame();
}

void GameInfoViewer::UpdateText()
{
    QString headerText = QString::number(gameSetting->level)+"×"+QString::number(gameSetting->level)+" Game_"+QString::number(gameSetting->gameNo) + "/" + QString::number(GameData::GameMaxNo[gameSetting->level-GameData::GameMinLevel]);
    QString infoText = "flows: "+QString::number(gameSetting->currentflows)+" / "+QString::number(gameSetting->colorNumber)+
            "\r\npipe: "+QString::number(gameSetting->pipeFilled)+"%"+
            "\r\nmoves: "+QString::number(gameSetting->moves)+
            "\r\nbest: ";
    if(gameSetting->best>0)
        infoText += QString::number(gameSetting->best);

    header->setText(headerText);
    info->setText(infoText);
}
