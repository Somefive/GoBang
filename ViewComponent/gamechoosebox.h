#ifndef GAMECHOOSEBOX_H
#define GAMECHOOSEBOX_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QList>

#include "gamebutton.h"

class GameChooseBox : public QWidget
{
    Q_OBJECT

private slots:
    void Clicked(GameButton*);

protected:

    const int ItemCount;

    QList<GameButton*> ButtonList;

    QStringList* Choices;
    int Current;
    bool Folded;

    virtual void wheelEvent(QWheelEvent *);
    virtual void paintEvent(QPaintEvent *);

    void ButtonsUpdate();

public:

    QString Value();
    void setCurrent(int _No);
    explicit GameChooseBox(QWidget *parent, int _itemCount);
    void Add(const QString& _item);
    void RemoveLastItem();
    void setChoicesSource(QStringList* _source);
    void setFontSize(int px);
    int Count();

signals:

public slots:

};

#endif // GAMECHOOSEBOX_H
