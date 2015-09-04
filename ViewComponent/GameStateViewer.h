#ifndef GAMESTATEVIEWER_H
#define GAMESTATEVIEWER_H

#include <QObject>
#include <QWidget>

#include "gameviewpanel.h"
#include "gamebutton.h"
#include <QTimer>
#include <QLabel>
#include "global.h"

using namespace Global;

class GameStateViewer : public GameViewPanel
{
    Q_OBJECT
private:
    int* restTime;
    int* selfTimeUsed;
    int* opponentTimeUsed;
    STATE* BlackTurn;
    STATE isBlack;
    QTimer timer;
    QLabel* Title;
    QLabel* restTimeViewer;
    QLabel* usedTimeViewer;
    GameButton* undoButton;
    GameButton* quitButton;
    GameButton* loadButton;
    GameButton* saveButton;
protected:
    virtual void paintEvent(QPaintEvent *);
public:
    GameStateViewer(QWidget* parent,int *_restTime,int *_selfTimeUsed,int *_opponentTimeUsed,STATE *_blackTurn,STATE _isBlack);
signals:
    void UndoButtonClicked();
    void QuitButtonClicked();
    void LoadButtonClicked();
    void SaveButtonClicked();
};

#endif // GAMESTATEVIEWER_H
