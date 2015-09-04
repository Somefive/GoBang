#include "mainwindow.h"
#include "gameController.h"
#include "GamePanel.h"
#include "ViewComponent/GameEnterNumberBox.h"
#include <QApplication>
#include "ViewComponent/GameEntranceInterface.h"
#include <ViewComponent/GameStateViewer.h>
#include <ViewComponent/GameLoadFilePanel.h>

#include "ViewComponent/GameTypeBox.h"
#include "ViewComponent/GameMessageViewer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
