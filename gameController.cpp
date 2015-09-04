#include "gameController.h"
#include "Message/someMessageManager.h"
#include "Message/someCoordinateMessage.h"
#include "Message/someNotifyMessage.h"
#include "Message/someTimeCountMessage.h"
#include "Message/somePlainMessage.h"
#include <QCoreApplication>

#include <QFile>
#include <QTextStream>
#include <QDebug>

#include <Message/someChatMessage.h>

GameController::GameController(QWidget *parent) :
    QWidget(parent),SelfTotalTimeUsed(0),OpponentTotalTimeUsed(0),UndoRestTime(2),
    Parent(parent)
{
    this->setGeometry(parent->rect());

    Panel = new GamePanel(this);

    Turn = BLACK;
    timer.setInterval(1000);
    connect(&timer,SIGNAL(timeout()),this,SLOT(TimeTick()));

    for(int i=0;i<15;++i)
        for(int j=0;j<15;++j)
            setState(QPoint(i,j),BLANK);
}

bool GameController::Save(const QString &filePath)
{
    QFile file(QCoreApplication::applicationDirPath()+"/Resources/Data/"+filePath);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream stream(&file);
    for(int i=0;i<15;++i)
    {
        for(int j=0;j<15;++j)
        {
            if(ChessState[i][j]==WHITE)
                stream<<"W";
            else if(ChessState[i][j]==BLACK)
                stream<<"B";
            else
                stream<<"N";
        }
    }
    if(Turn==BLACK)
        stream<<"B";
    else
        stream<<"N";
    file.close();
    return true;
}

bool GameController::Load(const QString &filePath)
{
    QFile file(QCoreApplication::applicationDirPath()+"/Resources/Data/"+filePath);
    if(!file.exists())
        return false;
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream stream(&file);
    QString info = stream.readAll();
    for(int i=0;i<15;++i)
    {
        for(int j=0;j<15;++j)
        {
            if(info.at(i)=='B')
                ChessState[i][j] = BLACK;
            else if(info.at(i)=='W')
                ChessState[i][j] = WHITE;
            else
                ChessState[i][j] = BLANK;
        }
    }
    if(info.at(info.size()-1)=='B')
        Turn = BLACK;
    else
        Turn = WHITE;
    file.close();
    return true;
}

void GameController::Load(someLoadMessage *lmsg)
{
    qDebug()<<"Loading...";
    Clear();
    for(int i=0;i<15;++i)
    {
        for(int j=0;j<15;++j)
        {
            if(lmsg->Map.at(i*15+j)=='B')
                ChessState[i][j] = BLACK;
            else if(lmsg->Map.at(i*15+j)=='W')
                ChessState[i][j] = WHITE;
            else
                ChessState[i][j] = BLANK;
        }
    }
    if(lmsg->Turn=='B')
        Turn = BLACK;
    else
        Turn = WHITE;
    StartNewGame();
}

STATE GameController::getState(const QPoint &_coordinate)
{
    if(!ExistValid(_coordinate))
        return BLANK;
    return ChessState[_coordinate.x()][_coordinate.y()];
}

void GameController::setState(const QPoint &_coordinate, STATE _state)
{
    if(ExistValid(_coordinate))
        ChessState[_coordinate.x()][_coordinate.y()] = _state;
}

bool GameController::ExistValid(const QPoint &_coordinate)
{
    if(_coordinate.x()<0||_coordinate.x()>=15)
        return false;
    if(_coordinate.y()<0||_coordinate.y()>=15)
        return false;
    return true;
}

bool GameController::PlaceValid(const QPoint &_coordinate)
{
    if(!ExistValid(_coordinate))
        return false;
    if(getState(_coordinate)!=BLANK)
        return false;
    return true;
}

bool GameController::CheckWin(const QPoint &_last)
{
    STATE oriState = getState(_last);
    static int dct[4][2] = {{1,0},{0,1},{1,1},{1,-1}};
    for(int k=0;k<4;++k)
    {
        int suce = 1;
        for(int i=1;i<5;++i)
        {
            QPoint p(_last.x()+dct[k][0]*i,_last.y()+dct[k][1]*i);
            if(ExistValid(p)&&getState(p)==oriState)
                suce++;
            else
                break;
        }
        for(int i=1;i<5;++i)
        {
            QPoint p(_last.x()-dct[k][0]*i,_last.y()-dct[k][1]*i);
            if(ExistValid(p)&&getState(p)==oriState)
                suce++;
            else
                break;
        }
        if(suce>=5)
            return true;
    }
    return false;
}


void GameController::Operate(someMessage *msg,STATE _state)
{
    qDebug()<<"Operate Message:"<<msg->ToString()<<" STATE:"<<_state<<" SelfState:"<<SelfState;
    if(_state==SelfState)
        emit SendMessage(msg);

    qDebug()<<"msgType:"<<msg->MessageType;
    someMessageManager::TYPE msgType = someMessageManager::getType(msg->MessageType);

    switch(msgType)
    {
    case someMessageManager::COORDINATE:
    {
        someCoordinateMessage* cmsg = static_cast<someCoordinateMessage*>(msg);
        setState(cmsg->data,_state);
        if(_state==SelfState)
            SelfChessMen.push_back(cmsg->data);
        else
            OpponentChessMen.push_back(cmsg->data);
        emit PlayAudio("NewChess.wav");
        if(CheckWin(cmsg->data))
        {
            if(_state==SelfState)
            {
                Panel->WinGame();
                emit PlayAudio("Victory.wav");
            }
            else
            {
                Panel->LoseGame();
                emit PlayAudio("Failed.wav");
            }
        }
        else
            TakeTurn();
        break;
    }
    case someMessageManager::TIMECOUNT:
    {
        someTimeCountMessage* tcmsg = static_cast<someTimeCountMessage*>(msg);
        if(_state==SelfState)
            SelfTotalTimeUsed += tcmsg->TimeCount;
        else
            OpponentTotalTimeUsed += tcmsg->TimeCount;
        qDebug()<<SelfTotalTimeUsed<<"|"<<OpponentTotalTimeUsed;
        break;
    }
    case someMessageManager::NOTIFY:
    {
        someNotifyMessage* nmsg = static_cast<someNotifyMessage*>(msg);
        NotifyMessageHandler(nmsg,_state);
        break;
    }
    case someMessageManager::LOAD:
    {
        someLoadMessage* lmsg = static_cast<someLoadMessage*>(msg);
        Load(lmsg);
        break;
    }
    case someMessageManager::CHAT:
    {
        someChatMessage* cmsg = static_cast<someChatMessage*>(msg);
        if(!cmsg->chatMessage.endsWith(".wav"))
            emit UiUpdateChatMessage(cmsg);
        if(cmsg->chatMessage.endsWith(".wav"))
            emit PlayAudio("Chat/"+cmsg->chatMessage);
        else if(_state!=SelfState)
            emit PlayAudio("Chat.wav");
        break;
    }
    default:
        break;
    }
    emit UiUpdateChess();
}

void GameController::StartNewGame()
{
    restTime = TurnMaxTime;
    if(SelfState==BLACK)
    {
        Panel->Able = true;
        timer.start();
    }
    emit PlayAudio("Start");
}

void GameController::GainMessageFromOpponent(someMessage *msg)
{
    if(SelfState==BLACK)
        Operate(msg,WHITE);
    else if(SelfState==WHITE)
        Operate(msg,BLACK);
}

void GameController::Clear()
{
    SelfChessMen.clear();
    OpponentChessMen.clear();
    UndoRestTime = 2;
    SelfTotalTimeUsed = 0;
    OpponentTotalTimeUsed = 0;
    restTime = TurnMaxTime;
    for(int i=0;i<15;++i)
        for(int j=0;j<15;++j)
            ChessState[i][j] = BLANK;
    Panel->update();
}

void GameController::paintEvent(QPaintEvent *)
{
    this->setGeometry(Parent->rect());
}

void GameController::TakeTurn()
{
    UndoRestTime = 2;
    timer.stop();
    if(Turn==SelfState)
    {
        someTimeCountMessage *tcmsg = new someTimeCountMessage(this,TurnMaxTime-restTime);
        Operate(tcmsg,SelfState);
    }
    restTime = TurnMaxTime;
    if(Turn==BLACK)
        Turn=WHITE;
    else if(Turn==WHITE)
        Turn=BLACK;
    if(Turn==SelfState)//处理开始下一轮
    {
        timer.start();
        Panel->Able = true;
    }
    else
    {
        Panel->Able = false;
    }
    emit UiYourTurn(Turn==SelfState);
}

void GameController::NotifyMessageHandler(someNotifyMessage *nmsg,STATE _state)
{
    static bool ReadyToQuit = false;
    static bool ReadyToUndo = false;
    static bool ReadyToLoad = false;
    switch(nmsg->NotifyType)
    {
    case someMessageManager::TIMEOUT:
        if(_state==SelfState)
            emit UiTimeOutInfomation();
        TakeTurn();
        break;
    case someMessageManager::QUIT:
        if(_state!=SelfState)
            emit UiRequestForQuit();
        else
            emit UiWaitForResponse();
        ReadyToQuit=true;
        break;
    case someMessageManager::UNDO:
        if(UndoRestTime<=0)
            break;
        ReadyToUndo=true;
        if(_state!=SelfState && OpponentChessMen.size()>=1)
            emit UiRequestForUndo();
        else if(_state==SelfState && SelfChessMen.size()>=1)
            emit UiWaitForResponse();
        break;
    case someMessageManager::QLOAD:
        ReadyToLoad = true;
        if(_state==SelfState)
            emit UiWaitForResponse();
        else if(_state!=SelfState)
            emit UiRequestForLoad();
        break;
    case someMessageManager::YES:
        if(_state!=SelfState)
            emit UiFetchResponse(true);
        if(ReadyToQuit)
        {
            ReadyToQuit = false;
            emit QuitGame();
        }
        if(ReadyToUndo)
        {
            ReadyToUndo = false;
            UndoRestTime--;
            setState(SelfChessMen.back(),BLANK);
            setState(OpponentChessMen.back(),BLANK);
            SelfChessMen.pop_back();
            OpponentChessMen.pop_back();
            emit UiUpdateChess();
        }
        if(ReadyToLoad)
        {
            ReadyToLoad = false;
            if(_state!=SelfState)
                emit UiAllowedToLoad();
        }
        break;
    case someMessageManager::NO:
        if(_state!=SelfState)
            emit UiFetchResponse(false);
        ReadyToQuit = false;
        ReadyToUndo = false;
        ReadyToLoad = false;
        break;

    default:
        break;
    }
}

void GameController::TimeTick()
{
    --restTime;
    if(restTime<=0)
    {
        someNotifyMessage* nmsg = new someNotifyMessage(this,someMessageManager::TIMEOUT);
        Operate(nmsg,SelfState);
    }
}





