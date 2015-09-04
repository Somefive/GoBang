#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Test/someClientTest.h"
#include "Test/someServerTest.h"
#include "Message/someMessageClient.h"
#include "Message/someMessageServer.h"

#include <QDebug>

#include <ViewComponent/GameEnterNumberBox.h>
#include <ViewComponent/gamemessagebox.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    backSlider = new GameBackSliderPlayer(this);
    backSlider->show();

    entranceInterface = new GameEntranceInterface(this);
    entranceInterface->show();
//    entranceInterface->hide();

    controller = new GameController(this);
    controller->hide();

    audioPlayer = new GameAudioPlayer(this);

    connect(entranceInterface,SIGNAL(StartGame(someMessageCommunicator*)),this,SLOT(StartGame(someMessageCommunicator*)));
    connect(controller,SIGNAL(PlayAudio(QString)),audioPlayer,SLOT(Play(QString)));
    connect(controller,SIGNAL(QuitGame()),this,SLOT(QuitGame()));
    connect(controller,SIGNAL(FinishGame()),this,SLOT(QuitGame()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::StartGame(someMessageCommunicator* _communicator)
{
    communicator = _communicator;
    connect(controller,SIGNAL(SendMessage(someMessage*)),communicator,SLOT(SendMessage(someMessage*)));
    connect(communicator,SIGNAL(GainMessage(someMessage*)),controller,SLOT(GainMessageFromOpponent(someMessage*)));
    if(communicator->isServer)
        controller->SelfState = BLACK;
    else
        controller->SelfState = WHITE;
    entranceInterface->hide();
    controller->show();
    controller->StartNewGame();
}

void MainWindow::QuitGame()
{
    controller->Clear();
    controller->hide();
    if(communicator!=NULL)
        communicator->deleteLater();
    entranceInterface->show();
}
