#include "GameEntranceInterface.h"
#include "gamemessagebox.h"
#include "mypainter.h"

#include "gamemessagebox.h"
#include <Message/someMessageClient.h>
#include <Message/someMessageServer.h>

void GameEntranceInterface::paintEvent(QPaintEvent *event)
{
    GameViewPanel::paintEvent(event);
    MyPainter painter(this);
    int _w = width(), _h = height();
    Title->setGeometry(_w*0.25,_h*0.15,_w*0.5,_h*0.2);
    ServerBtn->setGeometry(_w*0.3,_h*0.5,_w*0.4,_h*0.1);
    ClientBtn->setGeometry(_w*0.3,_h*0.65,_w*0.4,_h*0.1);
    Author->setGeometry(_w*0.7,_h*0.85,_w*0.3,_h*0.1);
    QPalette palette;
    QFont font;
    palette.setBrush(QPalette::WindowText,Qt::white);
    Title->setPalette(palette);
    font.setFamily("Lucida Handwriting");
    font.setPixelSize(Title->height()*0.4);
    Title->setFont(font);
    palette.setBrush(QPalette::WindowText,Qt::gray);
    Author->setPalette(palette);
    font.setFamily("Lucida Calligraphy");
    font.setPixelSize(Author->height()*0.25);
    Author->setFont(font);
}

GameEntranceInterface::GameEntranceInterface(QWidget *parent):
    GameViewPanel(parent),communicator(NULL)
{
    this->setGeometry(parent->rect());
    GameViewPanel::setMoveState(false);
    ServerBtn = new GameSizeChangeButton("Server",this);
    ServerBtn->setRatio(1.5,1.5);
    ClientBtn = new GameSizeChangeButton("Client",this);
    ServerBtn->setRatio(1.5,1.5);
    Title = new QLabel("Gobang",this);
    Title->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    Author = new QLabel("via Somefive",this);

    waitingMsgBox = new GameMessageBox(this,"Connecting...","Your IP Address is\n\r"+someMessageCommunicator::LocalIP(),"Cancel");
    waitingMsgBox->hide();
    enterIPBox = new GameEnterNumberBox(this);
    enterIPBox->hide();

    connect(ServerBtn,SIGNAL(Clicked()),this,SLOT(ServerBtnClicked()));
    connect(ClientBtn,SIGNAL(Clicked()),this,SLOT(ClientBtnClicked()));

    connect(waitingMsgBox,SIGNAL(CentralButtonClicked()),this,SLOT(ConnectionCanceled()));
    connect(waitingMsgBox,SIGNAL(CentralButtonClicked()),waitingMsgBox,SLOT(hide()));

}


void GameEntranceInterface::ServerBtnClicked()
{
    waitingMsgBox->show();
    communicator = new someMessageServer(this);
    ClientBtn->setDisabled(true);
    ServerBtn->setDisabled(true);
    connect(communicator,SIGNAL(ConnectionEstablished()),this,SLOT(ConnectionEstablished()));
    connect(communicator,SIGNAL(ConnectionEstablished()),waitingMsgBox,SLOT(hide()));
    connect(communicator,SIGNAL(ConnectionFailed(QAbstractSocket::SocketError)),this,SLOT(ConnectionFailed(QAbstractSocket::SocketError)));
    connect(communicator,SIGNAL(ConnectionFailed(QAbstractSocket::SocketError)),waitingMsgBox,SLOT(hide()));
}

void GameEntranceInterface::ClientBtnClicked()
{
    enterIPBox->show();
    enterIPBox->setFocus();
    communicator = new someMessageClient(this);
    ServerBtn->setDisabled(true);
    ClientBtn->setDisabled(true);
    connect(enterIPBox,SIGNAL(EmitIP(QString)),this,SLOT(ClientTryToConnect(QString)));
    connect(enterIPBox,SIGNAL(EmitIP(QString)),enterIPBox,SLOT(hide()));
}

void GameEntranceInterface::ClientTryToConnect(const QString &_IP)
{
    communicator->Connect(_IP);
    waitingMsgBox->show();
    connect(communicator,SIGNAL(ConnectionEstablished()),this,SLOT(ConnectionEstablished()));
    connect(communicator,SIGNAL(ConnectionEstablished()),waitingMsgBox,SLOT(hide()));
    connect(communicator,SIGNAL(ConnectionFailed(QAbstractSocket::SocketError)),this,SLOT(ConnectionFailed(QAbstractSocket::SocketError)));
    connect(communicator,SIGNAL(ConnectionFailed(QAbstractSocket::SocketError)),waitingMsgBox,SLOT(hide()));
}

void GameEntranceInterface::ConnectionEstablished()
{
    ConnectionCanceled();
    emit StartGame(communicator);
}

void GameEntranceInterface::ConnectionFailed(QAbstractSocket::SocketError error)
{
    ConnectionCanceled();
    GameMessageBox *tmsgbox = new GameMessageBox(this,"Connection Failed...",QString::number(error),"OK");
    tmsgbox->show();
    connect(tmsgbox,SIGNAL(CentralButtonClicked()),tmsgbox,SLOT(hide()));
    connect(tmsgbox,SIGNAL(CentralButtonClicked()),tmsgbox,SLOT(deleteLater()));
    connect(this,SIGNAL(StartGame(someMessageCommunicator*)),tmsgbox,SLOT(hide()));
    connect(this,SIGNAL(StartGame(someMessageCommunicator*)),tmsgbox,SLOT(deleteLater()));
}

void GameEntranceInterface::ConnectionCanceled()
{
    ClientBtn->setEnabled(true);
    ServerBtn->setEnabled(true);
}



