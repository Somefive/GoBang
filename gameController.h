#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QWidget>
#include <vector>
#include <QTimer>
#include <Message/someChatMessage.h>
#include "Message/someMessage.h"
#include "Message/someNotifyMessage.h"
#include "Message/someLoadMessage.h"
#include "GamePanel.h"
#include "global.h"

using std::vector;

using namespace Global;

class GameController : public QWidget
{
    Q_OBJECT
    friend class GamePanel;
public:
    const int TurnMaxTime = 30;

    explicit GameController(QWidget *parent = 0);

    bool Save(const QString& filePath);
    bool Load(const QString& filePath);
    void Load(someLoadMessage*);

    STATE getState(const QPoint& _coordinate);
    void setState(const QPoint& _coordinate, STATE _state);
    bool ExistValid(const QPoint&);
    bool PlaceValid(const QPoint&);

    STATE Turn;
    STATE SelfState;

private:

    QWidget* Parent;

    GamePanel* Panel;

    STATE ChessState[15][15];
    QTimer timer;
    int restTime;
    int SelfTotalTimeUsed;
    int OpponentTotalTimeUsed;
    int UndoRestTime;
    vector<QPoint> SelfChessMen;
    vector<QPoint> OpponentChessMen;

    bool CheckWin(const QPoint&);

protected:
    virtual void paintEvent(QPaintEvent *);

signals:
    void SendMessage(someMessage*);
    void UiUpdateChess();
    void UiUpdateChatMessage(someChatMessage*);//ToLink
    void UiRequestForQuit();
    void UiRequestForUndo();
    void UiRequestForLoad();
    void UiWaitForResponse();
    void UiFetchResponse(bool);
    void UiAllowedToLoad();
    void QuitGame();
    void FinishGame();
    void PlayAudio(const QString&);
    void UiTimeOutInfomation();
    void UiYourTurn(bool);
public slots:
    void TakeTurn();
    void Operate(someMessage* msg,STATE _state);
    void StartNewGame();
    void GainMessageFromOpponent(someMessage* msg);
    void Clear();
private slots:
    void NotifyMessageHandler(someNotifyMessage*,STATE);
    void TimeTick();
};

#endif // GAMECONTROLLER_H
