#include "GamePanel.h"
#include "gameController.h"
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>
#include <Message/someCoordinateMessage.h>
#include <QTime>
#include "ViewComponent/gamemessagebox.h"
#include "ViewComponent/GameLoadFilePanel.h"

void GamePanel::PaintChessBoard(QPainter &painter)
{
    painter.setBrush(QBrush(QColor(127,127,127,160)));
    painter.setPen(Qt::NoPen);
    painter.drawRect(this->rect());
    painter.setBrush(QBrush(Qt::black));
    painter.setPen(QPen(QBrush(Qt::black),3));
    for(int i=-16;i<=16;i+=2)
    {
        if(abs(i)==16)
        {
            painter.save();
            painter.setPen(QPen(QBrush(Qt::black),7));
        }
        painter.drawLine(i*xR+wcenter,-16*yR+hcenter,i*xR+wcenter,+16*yR+hcenter);
        painter.drawLine(-16*xR+wcenter,i*yR+hcenter,+16*xR+wcenter,i*yR+hcenter);
        if(abs(i)==16)
            painter.restore();
    }
    painter.setPen(QPen(QBrush(Qt::black),12));
    painter.drawPoint(wcenter,hcenter);
    painter.drawPoint(-8*xR+wcenter,-8*yR+hcenter);
    painter.drawPoint(-8*xR+wcenter,+8*yR+hcenter);
    painter.drawPoint(+8*xR+wcenter,+8*yR+hcenter);
    painter.drawPoint(+8*xR+wcenter,-8*yR+hcenter);

}

void GamePanel::PaintCursor(QPainter &painter)
{
    QPoint _pos = Center(cursorCoordinate);
    painter.setPen(QPen(QBrush(QColor(255,255,80,200)),3));
    double s=0.25,l=1.25;
    int c[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};
    for(int i=0;i<4;++i)
    {
        double xr = xR*c[i][0], yr = yR*c[i][1];
        painter.drawLine(_pos.x()-xr*s,_pos.y()-yr*l,_pos.x()-xr*s,_pos.y()-yr*s);
        painter.drawLine(_pos.x()-xr*l,_pos.y()-yr*s,_pos.x()-xr*s,_pos.y()-yr*s);
    }
}

void GamePanel::PaintChessMen(QPainter &painter)
{
    painter.setPen(Qt::NoPen);
//    if(controller->SelfState==BLACK)
//        painter.setBrush(QBrush(Qt::black));
//    else
//        painter.setBrush(QBrush(Qt::white));
//    for(int i=0;i<controller->SelfChessMen.size();++i)
//    {
//        QPoint& _coordinate = controller->SelfChessMen.at(i);
//        double coe = 0.8;
//        QPoint center = Center(_coordinate);
//        painter.drawEllipse(center,coe*xR,coe*yR);
//    }
//    if(controller->SelfState==BLACK)
//        painter.setBrush(QBrush(Qt::white));
//    else
//        painter.setBrush(QBrush(Qt::black));
//    for(int i=0;i<controller->OpponentChessMen.size();++i)
//    {
//        QPoint& _coordinate = controller->OpponentChessMen.at(i);
//        double coe = 0.8;
//        QPoint center = Center(_coordinate);
//        painter.drawEllipse(center,coe*xR,coe*yR);
//    }
    for(int i=0;i<15;++i)
    {
        for(int j=0;j<15;++j)
        {
            STATE _state = controller->getState(QPoint(i,j));
            if(_state==BLACK)
                painter.setBrush(QBrush(Qt::black));
            else if(_state==WHITE)
                painter.setBrush(QBrush(Qt::white));
            if(_state!=BLANK)
            {
                QPoint center = Center(QPoint(i,j));
                painter.drawEllipse(center,0.8*xR,0.8*yR);
            }
        }
    }
}

void GamePanel::UpdateSize()
{
    this->setGeometry(controller->rect());
    xR = this->width()/(30+xOffset*2), yR = this->height()/(30+yOffset*2);
    wcenter = this->width()/2, hcenter = this->height()/2;
}

void GamePanel::paintEvent(QPaintEvent *)
{
    UpdateSize();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    PaintChessBoard(painter);
    PaintCursor(painter);
    PaintChessMen(painter);
}

void GamePanel::mouseMoveEvent(QMouseEvent *event)
{
    if(Valid(event->pos()))
    {
        cursorCoordinate = Coordinate(event->pos());
        update();
    }
}

void GamePanel::mousePressEvent(QMouseEvent *event)
{
    if(Able&&event->button()==Qt::LeftButton)
    {
        QPoint _coordinate = Coordinate(event->pos());
        if(controller->PlaceValid(_coordinate))
        {
            someCoordinateMessage* cmsg = new someCoordinateMessage(this,_coordinate);
            controller->Operate(cmsg,controller->SelfState);
        }
    }
}

void GamePanel::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"presskey:"<<event->key();
    switch(event->key())
    {
    case Qt::Key_Control:
        if(stateViewer->isVisible())
            stateViewer->hide();
        else
            stateViewer->show();
        break;
    case Qt::Key_Alt:
        if(typeBox->isVisible())
        {
            typeBox->hide();
            messageViewer->hide();
        }
        else
        {
            typeBox->show();
            messageViewer->show();
            typeBox->setFocus();
        }
        break;
    default:
        break;
    }
}

GamePanel::GamePanel(GameController *parent) :
    QWidget(parent), controller(parent),
    xOffset(2), yOffset(2)
{
    Able = false;

    this->setGeometry(parent->rect());
    this->setMouseTracking(true);
    connect(controller,SIGNAL(UiWaitForResponse()),this,SLOT(WaitForResponse()));
    connect(controller,SIGNAL(UiUpdateChess()),this,SLOT(update()));
    connect(controller,SIGNAL(UiRequestForQuit()),this,SLOT(RequestForQuit()));
    connect(controller,SIGNAL(UiRequestForUndo()),this,SLOT(RequestForUndo()));
    connect(controller,SIGNAL(UiRequestForLoad()),this,SLOT(RequestForLoad()));
    connect(controller,SIGNAL(UiAllowedToLoad()),this,SLOT(AllowedToLoad()));
    connect(controller,SIGNAL(UiFetchResponse(bool)),this,SLOT(FetchConfirmMessage(bool)));


    connect(controller,SIGNAL(UiTimeOutInfomation()),this,SLOT(TimeOutInfomation()));
    connect(controller,SIGNAL(UiYourTurn(bool)),this,SLOT(YourTurn(bool)));

    stateViewer = new GameStateViewer(this,&(controller->restTime),&(controller->SelfTotalTimeUsed),&(controller->OpponentTotalTimeUsed),
                                      &(controller->Turn),(controller->SelfState));
    stateViewer->show();

    connect(stateViewer,SIGNAL(UndoButtonClicked()),this,SLOT(AskForUndo()));
    connect(stateViewer,SIGNAL(QuitButtonClicked()),this,SLOT(AskForQuit()));
    connect(stateViewer,SIGNAL(LoadButtonClicked()),this,SLOT(AskForLoad()));
    connect(stateViewer,SIGNAL(SaveButtonClicked()),this,SLOT(AskForSave()));

    messageViewer = new GameMessageViewer(this);
    messageViewer->hide();

    typeBox = new GameTypeBox(this);
    typeBox->hide();

    connect(controller,SIGNAL(UiUpdateChatMessage(someChatMessage*)),this,SLOT(UpdateChatMessage(someChatMessage*)));
    connect(typeBox,SIGNAL(EmitText(QString)),this,SLOT(SendChatMessage(QString)));
    connect(typeBox,SIGNAL(EmitText(QString)),typeBox,SLOT(hide()));
    connect(typeBox,SIGNAL(EmitText(QString)),messageViewer,SLOT(hide()));

    this->setFocusPolicy(Qt::StrongFocus);
}

QPoint GamePanel::Coordinate(const QPoint &_pos)
{
    int _x = (_pos.x()+xR*2)/xR/2 - xOffset;
    int _y = (_pos.y()+yR*2)/yR/2 - yOffset;
    return QPoint(_x,_y);
}

QPoint GamePanel::Center(const QPoint &_coordinate)
{
    double _x = wcenter+(_coordinate.x()-7)*2*xR;
    double _y = hcenter+(_coordinate.y()-7)*2*yR;
    return QPoint(_x,_y);
}

bool GamePanel::Valid(const QPoint &_pos)
{
    QPoint _coordinate = Coordinate(_pos);
    if(_coordinate.x()<0 || _coordinate.x()>=15)
        return false;
    if(_coordinate.y()<0 || _coordinate.y()>=15)
        return false;
    return true;
}

void GamePanel::AskForUndo()
{
    someNotifyMessage* nmsg = new someNotifyMessage(this,someMessageManager::UNDO);
    controller->Operate(nmsg,controller->SelfState);
}

void GamePanel::AskForQuit()
{
    someNotifyMessage* nmsg = new someNotifyMessage(this,someMessageManager::QUIT);
    controller->Operate(nmsg,controller->SelfState);
}

void GamePanel::AskForLoad()
{
    someNotifyMessage* nmsg = new someNotifyMessage(this,someMessageManager::QLOAD);
    controller->Operate(nmsg,controller->SelfState);
}

void GamePanel::AskForSave()
{
    QString path = QDate::currentDate().toString("yy_M_d_")+QTime::currentTime().toString("h_m")+".txt";
    if(controller->Save(path))
    {
        GameMessageBox* msgBox = new GameMessageBox(this,"Success","Save Success in "+path,"OK");
        msgBox->show();
        connect(msgBox,SIGNAL(CentralButtonClicked()),msgBox,SLOT(hide()));
        connect(msgBox,SIGNAL(CentralButtonClicked()),msgBox,SLOT(deleteLater()));
        QTimer::singleShot(1000,msgBox,SIGNAL(CentralButtonClicked()));
    }
}

void GamePanel::WaitForResponse()
{
    Able = false;
    GameMessageBox* msgBox = new GameMessageBox(this,"Waiting...","Wait For Response.","OK");
    msgBox->show();
    connect(msgBox,SIGNAL(CentralButtonClicked()),msgBox,SLOT(hide()));
    connect(msgBox,SIGNAL(CentralButtonClicked()),msgBox,SLOT(deleteLater()));
    connect(controller,SIGNAL(UiFetchResponse(bool)),msgBox,SLOT(hide()));
    connect(controller,SIGNAL(UiFetchResponse(bool)),msgBox,SLOT(deleteLater()));
}

void GamePanel::RequestForQuit()
{
    GameMessageBox* msgbox = new GameMessageBox(this,"Request","Your Opponent is requesting for quitting.","Yes","No");
    msgbox->show();
    connect(msgbox,SIGNAL(LeftButtonClicked()),this,SLOT(SendYesMessage()));
    connect(msgbox,SIGNAL(RightButtonClicked()),this,SLOT(SendNoMessage()));
    connect(msgbox,SIGNAL(LeftButtonClicked()),msgbox,SLOT(hide()));
    connect(msgbox,SIGNAL(RightButtonClicked()),msgbox,SLOT(hide()));
    connect(msgbox,SIGNAL(LeftButtonClicked()),msgbox,SLOT(deleteLater()));
    connect(msgbox,SIGNAL(RightButtonClicked()),msgbox,SLOT(deleteLater()));
}

void GamePanel::RequestForUndo()
{
    GameMessageBox* msgbox = new GameMessageBox(this,"Request","Your Opponent is requesting for an undo.","Yes","No");
    msgbox->show();
    connect(msgbox,SIGNAL(LeftButtonClicked()),this,SLOT(SendYesMessage()));
    connect(msgbox,SIGNAL(RightButtonClicked()),this,SLOT(SendNoMessage()));
    connect(msgbox,SIGNAL(LeftButtonClicked()),msgbox,SLOT(hide()));
    connect(msgbox,SIGNAL(RightButtonClicked()),msgbox,SLOT(hide()));
    connect(msgbox,SIGNAL(LeftButtonClicked()),msgbox,SLOT(deleteLater()));
    connect(msgbox,SIGNAL(RightButtonClicked()),msgbox,SLOT(deleteLater()));
}

void GamePanel::RequestForLoad()
{
    GameMessageBox* msgbox = new GameMessageBox(this,"Request","Your Opponent is requesting for loading.","Yes","No");
    msgbox->show();
    connect(msgbox,SIGNAL(LeftButtonClicked()),this,SLOT(SendYesMessage()));
    connect(msgbox,SIGNAL(RightButtonClicked()),this,SLOT(SendNoMessage()));
    connect(msgbox,SIGNAL(LeftButtonClicked()),msgbox,SLOT(hide()));
    connect(msgbox,SIGNAL(RightButtonClicked()),msgbox,SLOT(hide()));
    connect(msgbox,SIGNAL(LeftButtonClicked()),msgbox,SLOT(deleteLater()));
    connect(msgbox,SIGNAL(RightButtonClicked()),msgbox,SLOT(deleteLater()));
}

void GamePanel::FetchConfirmMessage(bool ans)
{
    Able = true;
    GameMessageBox* msgBox;
    if(ans==true)
    {
//        QMessageBox::information(this,"Response","Your Opponent has accepted your request.");
        msgBox = new GameMessageBox(this,"Response","Your Opponent has accepted your request.","OK");
    }
    else
    {
//        QMessageBox::information(this,"Response","Your Opponent has refused your request.");
        msgBox = new GameMessageBox(this,"Response","Your Opponent has refused your request.","OK");
    }
    msgBox->show();
    connect(msgBox,SIGNAL(CentralButtonClicked()),msgBox,SLOT(hide()));
    connect(msgBox,SIGNAL(CentralButtonClicked()),msgBox,SLOT(deleteLater()));
}

void GamePanel::WinGame()
{
    //QMessageBox::information(this,"Winner!","You have won the game!");
    GameMessageBox* msgBox = new GameMessageBox(this,"Winner","You have won the game!","Yeah!");
    msgBox->show();
    connect(msgBox,SIGNAL(CentralButtonClicked()),msgBox,SLOT(hide()));
    connect(msgBox,SIGNAL(CentralButtonClicked()),msgBox,SLOT(deleteLater()));
    connect(msgBox,SIGNAL(CentralButtonClicked()),controller,SIGNAL(FinishGame()));
}

void GamePanel::LoseGame()
{
//    QMessageBox::information(this,"Loser...","You lost the game...");
    GameMessageBox* msgBox = new GameMessageBox(this,"Loser...","You lost the game...","Pity...");
    msgBox->show();
    connect(msgBox,SIGNAL(CentralButtonClicked()),msgBox,SLOT(hide()));
    connect(msgBox,SIGNAL(CentralButtonClicked()),msgBox,SLOT(deleteLater()));
    connect(msgBox,SIGNAL(CentralButtonClicked()),controller,SIGNAL(FinishGame()));
}

void GamePanel::TimeOutInfomation()
{
    GameMessageBox* timeOutMsgBox = new GameMessageBox(this,"TimeOut!","You have been thinking overtime.","OK...");
    timeOutMsgBox->show();
    connect(timeOutMsgBox,SIGNAL(CentralButtonClicked()),timeOutMsgBox,SLOT(hide()));
    connect(timeOutMsgBox,SIGNAL(CentralButtonClicked()),timeOutMsgBox,SLOT(deleteLater()));
    QTimer::singleShot(1000,timeOutMsgBox,SIGNAL(CentralButtonClicked()));
}

void GamePanel::YourTurn(bool isYourTurn)
{
    /*
    QString content = "";
    if(isYourTurn)
        content += "It's time for your turn.";
    else
        content += "End Turn";
    GameMessageBox* msgBox = new GameMessageBox(this,"Take Turn",content,"OK");
    msgBox->show();
    connect(msgBox,SIGNAL(CentralButtonClicked()),msgBox,SLOT(hide()));
    connect(msgBox,SIGNAL(CentralButtonClicked()),msgBox,SLOT(deleteLater()));
    QTimer::singleShot(500,msgBox,SLOT(hide()));
    QTimer::singleShot(500,msgBox,SLOT(deleteLater()));*/
}

void GamePanel::SendYesMessage()
{
    someNotifyMessage* nmsg = new someNotifyMessage(this,someMessageManager::YES);
    controller->Operate(nmsg,controller->SelfState);
}

void GamePanel::SendNoMessage()
{
    someNotifyMessage* nmsg = new someNotifyMessage(this,someMessageManager::NO);
    controller->Operate(nmsg,controller->SelfState);
}

void GamePanel::AllowedToLoad()
{
    GameLoadFilePanel* loadFilePanel = new GameLoadFilePanel(this);
    loadFilePanel->show();
    connect(loadFilePanel,SIGNAL(ChooseLoadFile(QString)),this,SLOT(LoadGame(QString)));
}

#include <QCoreApplication>
void GamePanel::LoadGame(const QString& filePath)
{
    QFile file(QCoreApplication::applicationDirPath()+"/Resources/Data/"+filePath);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream stream(&file);
    QString _map = stream.readAll();
    QChar _turn = _map.at(_map.size()-1);
    file.close();
    someLoadMessage* lmsg = new someLoadMessage(this,_map,_turn);
    controller->Operate(lmsg,controller->SelfState);
}

void GamePanel::UpdateChatMessage(someChatMessage *msg)
{
    messageViewer->AddText("["+msg->owner+"]:\n"+msg->chatMessage);
    messageViewer->show();
    QTimer::singleShot(1500,messageViewer,SLOT(hide()));
}

void GamePanel::SendChatMessage(const QString &msg)
{
    someChatMessage* cmsg = new someChatMessage(this,msg,controller->SelfState==BLACK?"BLACK":"WHITE");
    controller->Operate(cmsg,controller->SelfState);
}

