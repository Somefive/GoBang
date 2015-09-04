#ifndef GAMEMESSAGEBOX
#define GAMEMESSAGEBOX

#include "gameviewpanel.h"
#include "gamebutton.h"

#include <QWidget>
#include <QString>
#include <QLabel>

class GameMessageBox: public GameViewPanel
{
    Q_OBJECT

private slots:
    void leftButtonClicked();
    void rightButtonClicked();
    void centralButtonClicked();

signals:
    void LeftButtonClicked();
    void RightButtonClicked();
    void CentralButtonClicked();

private:

    QString Title;
    QString Content;

    QLabel* titleLabel;
    QLabel* contentLabel;

    GameButton* leftButton;
    GameButton* rightButton;
    GameButton* centralButton;

    void Initialize();

protected:

    virtual void paintEvent(QPaintEvent*);

public:

    GameMessageBox(QWidget *_widget,const QString& _title,const QString& _content,const QString& _leftText,const QString& _rightText);
    GameMessageBox(QWidget *_widget,const QString& _title,const QString& _content,const QString& _centralText);
    GameMessageBox(QWidget *_widget, const QString &_title, const QString &_content);
};

#endif // GAMEMESSAGEBOX

