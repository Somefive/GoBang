#include "GameStateViewer.h"
#include <QDebug>

void GameStateViewer::paintEvent(QPaintEvent *event)
{
    GameViewPanel::paintEvent(event);
    int w = width(), h = height();
    Title->setGeometry(w*0.05,h*0.15,w*0.18,h*0.7);
    restTimeViewer->setGeometry(w*0.25,h*0.15,w*0.23,h*0.7);
    usedTimeViewer->setGeometry(w*0.45,h*0.15,w*0.23,h*0.7);
    undoButton->setGeometry(w*0.7,h*0.15,w*0.12,h*0.3);
    quitButton->setGeometry(w*0.85,h*0.15,w*0.12,h*0.3);
    loadButton->setGeometry(w*0.7,h*0.55,w*0.12,h*0.3);
    saveButton->setGeometry(w*0.85,h*0.55,w*0.12,h*0.3);

    Title->setText(*BlackTurn==BLACK?"BLACK":"WHITE");
    restTimeViewer->setText("Time:"+QString::number(*restTime)+" s");
    if(isBlack==BLACK)
    {
        usedTimeViewer->setText("BLACK used: "+QString::number(*selfTimeUsed)+" s\r\n"+
                                "WHITE used: "+QString::number(*opponentTimeUsed)+" s");
    }
    else
    {
        usedTimeViewer->setText("WHITE used:"+QString::number(*selfTimeUsed)+" s\r\n"+
                                "BLACK used:"+QString::number(*opponentTimeUsed)+" s");
    }
}

GameStateViewer::GameStateViewer(QWidget *parent, int *_restTime, int *_selfTimeUsed, int *_opponentTimeUsed,STATE *_blackTurn,STATE _isBlack):
    GameViewPanel(parent),restTime(_restTime),selfTimeUsed(_selfTimeUsed),opponentTimeUsed(_opponentTimeUsed),BlackTurn(_blackTurn),isBlack(_isBlack)
{
    this->setGeometry(parent->width()*0.05,parent->height()*0.05,parent->width()*0.9,parent->height()*0.1);

    timer.setInterval(1000);
    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
    timer.start();

    QPalette palette;
    palette.setBrush(QPalette::WindowText,Qt::white);

    Title = new QLabel("Game State",this);
    Title->setPalette(palette);
    Title->setFont(QFont("Kristen ITC",16));
    Title->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    restTimeViewer = new QLabel(this);
    restTimeViewer->setPalette(palette);
    restTimeViewer->setFont(QFont("Franklin Gothic Book",14));
    restTimeViewer->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    palette.setBrush(QPalette::WindowText,Qt::yellow);
    usedTimeViewer = new QLabel(this);
    usedTimeViewer->setPalette(palette);
    usedTimeViewer->setFont(QFont("Franklin Gothic Book",10));
    usedTimeViewer->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    usedTimeViewer->setWordWrap(true);

    undoButton = new GameButton("Undo",this);
    quitButton = new GameButton("Quit",this);
    loadButton = new GameButton("Load",this);
    saveButton = new GameButton("Save",this);

    connect(undoButton,SIGNAL(Clicked()),this,SIGNAL(UndoButtonClicked()));
    connect(quitButton,SIGNAL(Clicked()),this,SIGNAL(QuitButtonClicked()));
    connect(loadButton,SIGNAL(Clicked()),this,SIGNAL(LoadButtonClicked()));
    connect(saveButton,SIGNAL(Clicked()),this,SIGNAL(SaveButtonClicked()));
}
