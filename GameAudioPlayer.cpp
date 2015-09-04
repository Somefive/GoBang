#include "GameAudioPlayer.h"
#include <QCoreApplication>
#include <QDebug>
#include <QFile>

GameAudioPlayer::GameAudioPlayer(QObject *parent):
    QObject(parent)
{
    rootPath = QCoreApplication::applicationDirPath()+"/Resources/Audio/";
//    background.setLoopCount(QSoundEffect::Infinite);
//    background.setSource(QUrl::fromLocalFile(rootPath+"Background.wav"));
//    background.setVolume(0.2);
    //background.play();

}

void GameAudioPlayer::Play(const QString &relativePath)
{
    QSound::play(rootPath+relativePath);
//    current.stop();
//    current.setSource(QUrl::fromLocalFile(rootPath+relativePath));
//    current.setLoopCount(1);
//    current.setVolume(1);
//    current.play();
}
