#ifndef GAMEVIEWPANEL
#define GAMEVIEWPANEL

#include <QString>
#include <QWidget>

class GameViewPanel: public QWidget
{
    Q_OBJECT

private:

protected:

    bool Fixed;

    QWidget* parent;

    QColor backColor;

    bool Moving;
    bool RightButtonPressed;
    QPoint LastWidgetPosition;
    QPoint LastCursorPosition;

    virtual void paintEvent(QPaintEvent*);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);

public:
    GameViewPanel(QWidget*);
    void setColor(const QColor& color);
    void setMoveState(bool movable=true);
    bool MuteRightButton;
};

#endif // GAMEVIEWPANEL

