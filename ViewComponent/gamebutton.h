#ifndef GAMEBUTTON
#define GAMEBUTTON

#include <QWidget>
#include <QString>
#include <QLabel>

class GameButton: public QWidget
{
    Q_OBJECT

signals:
    void Clicked();
    void Clicked(GameButton*);

public:
    enum GBSTATE{NORMAL,PRESSED,ENTERED};

protected:

    bool RoundedRim;
    QString Text;
    QColor textColorNormal, textColorPressed, textColorEntered;
    QColor backColorNormal, backColorPressed, backColorEntered;
    QColor textColor, backColor;

    QLabel* label;

    virtual void paintEvent(QPaintEvent *);
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);

public:
    GameButton(const QString&,QWidget*);
    void setFontSize(int px);
    int getFontSize();
    void setText(const QString& _text);
    void setColor(const QColor& _textColor,const QColor& _backColor,GBSTATE _state=NORMAL);
    void setRimShape(bool Rounded=true);
};

#endif // GAMEBUTTON

