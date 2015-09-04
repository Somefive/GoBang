#ifndef GAMEMESSAGEVIEWER_H
#define GAMEMESSAGEVIEWER_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include "gameviewpanel.h"

class GameMessageViewer : public GameViewPanel
{
    Q_OBJECT
private:
    QLabel* textViewer;
    QStringList texts;
    int MaxTextNumber;
protected:
    virtual void paintEvent(QPaintEvent *event);
public:
    GameMessageViewer(QWidget* parent);
public slots:
    void AddText(const QString&);
    void Clear();
};

#endif // GAMEMESSAGEVIEWER_H
