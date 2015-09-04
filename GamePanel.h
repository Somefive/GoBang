#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <QWidget>
#include <ViewComponent/gamemessagebox.h>
#include <ViewComponent/GameStateViewer.h>
#include <ViewComponent/GameMessageViewer.h>
#include <ViewComponent/GameTypeBox.h>
#include <QTimer>
#include <Message/someChatMessage.h>

class GameController;

class GamePanel : public QWidget
{
    Q_OBJECT
    friend class GameController;
private:
    GameController* controller;

    GameStateViewer* stateViewer;

    GameMessageViewer* messageViewer;
    GameTypeBox* typeBox;

    QPoint cursorCoordinate;


    double xR,yR,wcenter,hcenter;
    double xOffset, yOffset;

    void UpdateSize();

    void PaintChessBoard(QPainter& painter);
    void PaintCursor(QPainter& painter);
    void PaintChessMen(QPainter& painter);

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void keyPressEvent(QKeyEvent *);

public:
    explicit GamePanel(GameController *parent = 0);

    QPoint Coordinate(const QPoint& _pos);
    QPoint Center(const QPoint& _coordinate);
    bool Valid(const QPoint& _pos);

    bool Able;

signals:

private slots:
    void AskForUndo();
    void AskForQuit();
    void AskForLoad();
    void AskForSave();

public slots:
    void WaitForResponse();
    void RequestForQuit();
    void RequestForUndo();
    void RequestForLoad();
    void FetchConfirmMessage(bool);
    void WinGame();
    void LoseGame();
    void TimeOutInfomation();
    void YourTurn(bool);
    void SendYesMessage();
    void SendNoMessage();
    void AllowedToLoad();
    void LoadGame(const QString&);
    void UpdateChatMessage(someChatMessage*);
    void SendChatMessage(const QString&);
};

#endif // GAMEPANEL_H
