#ifndef GAMEAUDIOPLAYER_H
#define GAMEAUDIOPLAYER_H

#include <QObject>
#include <QSound>
#include <QSoundEffect>

class GameAudioPlayer : public QObject
{
    Q_OBJECT
private:
    QSoundEffect background;
    QSoundEffect current;
    QString rootPath;
public:
    GameAudioPlayer(QObject* parent);
public slots:
    void Play(const QString& relativePath);
};

#endif // GAMEAUDIOPLAYER_H
