#ifndef GAMEMENUINTERFACE
#define GAMEMENUINTERFACE

#include "gameviewpanel.h"
#include <QLabel>
#include "gamesizechangebutton.h"

class GameMenuInterface: public GameViewPanel
{
    Q_OBJECT

signals:
    void StartGame(int _level,int _gameNo);
    void ChooseLevelMenu();

public slots:
    void ChooseFive();
    void ChooseSix();
    void ChooseSeven();
    void ChooseAddition();

private:
    void ButtonInitialize(GameSizeChangeButton* button);

protected:
    QLabel* Title;
    QLabel* Author;

    GameSizeChangeButton *Five;
    GameSizeChangeButton *Six;
    GameSizeChangeButton *Seven;
    GameSizeChangeButton *Addition;
    QImage* backImage;

    void InitializeComponent();

    virtual void paintEvent(QPaintEvent *);

public:

    GameMenuInterface(QWidget* _parent);

};

#endif // GAMEMENUINTERFACE

