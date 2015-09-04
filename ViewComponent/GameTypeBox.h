#ifndef GAMETYPEBOX_H
#define GAMETYPEBOX_H

#include <QObject>
#include <QWidget>
#include <QLabel>

#include "gameviewpanel.h"

class GameTypeBox : public GameViewPanel
{
    Q_OBJECT
private:
    QLabel* editBox;
    QString text;
    int MaxTypeLength;
private slots:
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
public:
    GameTypeBox(QWidget* parent);
signals:
    void EmitText(const QString&);
};

#endif // GAMETYPEBOX_H
