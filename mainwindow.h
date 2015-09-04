#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameController.h"
#include "GamePanel.h"
#include "Message/someMessageCommunicator.h"
#include "ViewComponent/GameBackSliderPlayer.h"
#include "ViewComponent/GameEntranceInterface.h"
#include "GameAudioPlayer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void StartGame(someMessageCommunicator*);
    void QuitGame();
private:
    Ui::MainWindow *ui;

    GameController *controller;
    someMessageCommunicator *communicator;
    GameEntranceInterface *entranceInterface;
    GameBackSliderPlayer* backSlider;
    GameAudioPlayer* audioPlayer;
};

#endif // MAINWINDOW_H
