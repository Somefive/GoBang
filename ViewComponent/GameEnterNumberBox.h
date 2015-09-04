#ifndef GAMEENTERNUMBERBOX_H
#define GAMEENTERNUMBERBOX_H

#include <QObject>
#include <QWidget>
#include <QSignalMapper>
#include "gamebutton.h"
#include "gameviewpanel.h"
#include <vector>

using std::vector;

class GameEnterNumberBox : public GameViewPanel
{
    Q_OBJECT
signals:
    void EmitIP(const QString&);
private slots:
    void ContentButtonClicked(const QString&);
    void Confirm();
private:
    QSignalMapper* mapper;
    GameButton* numberButton[10];
    GameButton* dotButton;
    GameButton* delButton;
    GameButton* OKButton;
    QLabel* inputbox;
    vector<char> input;
protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void keyPressEvent(QKeyEvent *);
public:
    GameEnterNumberBox(QWidget* parent);
};

#endif // GAMEENTERNUMBERBOX_H
