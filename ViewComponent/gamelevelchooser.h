#ifndef GAMELEVELCHOOSER_H
#define GAMELEVELCHOOSER_H

#include "gameviewpanel.h"
#include "gamechoosebox.h"
#include "gamebutton.h"
#include <QLabel>

class GameLevelChooser: public GameViewPanel
{
    Q_OBJECT

public slots:
    void ConfirmButtonPressed();
    void MenuButtonPressed();
signals:
    void StartGame(int,int);
    void BackToMenu();
private:

    QLabel* Title;
    QLabel* levelLabel;
    QLabel* gameNoLabel;
    GameChooseBox* levelChooser;
    GameChooseBox* gameNoChooser;
    GameButton* confirmButton;
    GameButton* menuButton;
    QStringList* levelList;
    QStringList* numList;
    QImage* backImage;

protected:
    void InitializeComponent();
    virtual void paintEvent(QPaintEvent *);

public:
    GameLevelChooser(QWidget* parent);


};

#endif // GAMELEVELCHOOSER_H
