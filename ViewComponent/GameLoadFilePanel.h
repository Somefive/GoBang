#ifndef GAMELOADFILEPANEL_H
#define GAMELOADFILEPANEL_H

#include <QObject>
#include <QWidget>
#include "gamebutton.h"
#include "gamechoosebox.h"
#include <QLabel>

#include "gameviewpanel.h"

class GameLoadFilePanel : public GameViewPanel
{
    Q_OBJECT
private:
    QLabel* Title;
    GameButton* ChooseButton;
    GameButton* CancelButton;
    GameChooseBox* ChooseBox;
    QStringList pathList;
protected:
    virtual void paintEvent(QPaintEvent *);
public:
    GameLoadFilePanel(QWidget*);
private slots:
    void ChooseButtonClicked();
signals:
    void ChooseLoadFile(const QString&);
};

#endif // GAMELOADFILEPANEL_H
