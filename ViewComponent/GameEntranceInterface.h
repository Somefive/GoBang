#ifndef GAMEENTRANCEINTERFACE_H
#define GAMEENTRANCEINTERFACE_H

#include <QObject>
#include <QWidget>

#include "gameviewpanel.h"
#include "gamebutton.h"
#include "gamesizechangebutton.h"
#include "gamemessagebox.h"
#include "GameEnterNumberBox.h"
#include "Message/someMessageCommunicator.h"

class GameEntranceInterface : public GameViewPanel
{
    Q_OBJECT

signals:
    void StartGame(someMessageCommunicator*);

private:

    QLabel* Title;
    QLabel* Author;
    GameSizeChangeButton* ServerBtn;
    GameSizeChangeButton* ClientBtn;
    GameMessageBox* waitingMsgBox;
    GameEnterNumberBox* enterIPBox;
    someMessageCommunicator* communicator;

protected:
    virtual void paintEvent(QPaintEvent *);
public:
    GameEntranceInterface(QWidget* parent);

private slots:
    void ServerBtnClicked();
    void ClientBtnClicked();
    void ClientTryToConnect(const QString&);
    void ConnectionEstablished();
    void ConnectionFailed(QAbstractSocket::SocketError);
    void ConnectionCanceled();
};

#endif // GAMEENTRANCEINTERFACE_H
