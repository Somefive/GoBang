#include "GameBackSliderPlayer.h"
#include <QCoreApplication>
#include <QFile>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTime>

GameBackSliderPlayer::GameBackSliderPlayer(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(parent->rect());
    QString rootPath = QCoreApplication::applicationDirPath() + "/Resources/Image/back ";
    for(int i=0;;++i)
    {
        QString picPath = rootPath + "(" + QString::number(i) + ").jpg";
        if(!QFile::exists(picPath))
            break;
        QPixmap newpic(picPath);
        pics.push_back(newpic.scaled(this->size(),Qt::KeepAspectRatioByExpanding));
    }
    viewer = new QLabel(this);
    viewer->setGeometry(this->rect());
    if(pics.size()>0)
    {
        qsrand(QTime::currentTime().second());
        Current = qrand()%pics.size();
        viewer->setPixmap(pics[Current]);
        connect(&timer,SIGNAL(timeout()),this,SLOT(ChangeSlide()));
        timer.setInterval(60000);
        timer.start();
    }
}

void GameBackSliderPlayer::ChangeSlide()
{
    Current = (Current+1)%pics.size();
    viewer->setPixmap(pics[Current]);
}
