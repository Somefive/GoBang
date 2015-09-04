#ifndef GAMEINFOVIEWER
#define GAMEINFOVIEWER

#include "gameviewpanel.h"
#include "GameSetting.h"
#include "gamebutton.h"
#include <QLabel>

class GameInfoViewer: public GameViewPanel
{
    Q_OBJECT

signals:
    void Retry();
    void BackToMenu();
    void NextGame();
    void PreviousGame();
    void AnswerGame();

private slots:
    void RetryButtonClicked();
    void BackToMenuButtonClicked();
    void NextButtonClicked();
    void PreviousButtonClicked();
    void AnswerButtonClicked();

private:
    GameSetting *gameSetting;
    GameButton* retryButton;
    GameButton* nextButton;
    GameButton* previosButton;
    GameButton* answerButton;
    GameButton* backToMenuButton;
    QLabel* header;
    QLabel* info;

    void Initialize();
    void UpdateText();

protected:
    virtual void paintEvent(QPaintEvent *);

public:

    GameInfoViewer(QWidget*,GameSetting*);

};

#endif // GAMEINFOVIEWER

