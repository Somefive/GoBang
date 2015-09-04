#ifndef GAMEBACKSLIDERPLAYER_H
#define GAMEBACKSLIDERPLAYER_H

#include <QWidget>
#include <vector>
#include <QTimer>
#include <QLabel>

using std::vector;

class GameBackSliderPlayer : public QWidget
{
    Q_OBJECT
private:
    vector<QPixmap> pics;
    QTimer timer;
    int Current;
    QLabel* viewer;
public:
    explicit GameBackSliderPlayer(QWidget *parent = 0);

signals:

public slots:

private slots:
    void ChangeSlide();
};

#endif // GAMEBACKSLIDERPLAYER_H
