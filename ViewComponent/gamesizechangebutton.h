#ifndef GAMESIZECHANGEBUTTON
#define GAMESIZECHANGEBUTTON

#include "gamebutton.h"

class GameSizeChangeButton: public GameButton
{
    Q_OBJECT
public:
    typedef int Alignment;
    enum {
        XCenter = 0x01,
        YCenter = 0x02
    };

private:
    double xRatio, yRatio;
    Alignment alignment;
    QRect OriginalRect;
    int OriginalPointSize;

protected:
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);

public:
    GameSizeChangeButton(const QString&,QWidget*);
    void setRatio(double _x,double _y);
    void setAlignment(Alignment _alignment);
};

#endif // GAMESIZECHANGEBUTTON

