#include "gamechoosebox.h"

GameChooseBox::GameChooseBox(QWidget *parent,int _itemCount) :
    QWidget(parent), ItemCount(_itemCount), Folded(true), Current(0)
{
    Choices = new QStringList();
    for(int i=0;i<ItemCount;++i)
    {
        GameButton* newButton = new GameButton("",this);
        newButton->hide();
        ButtonList.push_back(newButton);
        connect(newButton,SIGNAL(Clicked(GameButton*)),this,SLOT(Clicked(GameButton*)));
    }
    ButtonList.at(0)->show();
}

void GameChooseBox::ButtonsUpdate()
{
    int _w = width(), _h = height();
    for(int i=0;i<ItemCount&&i<Choices->size();++i)
    {
        GameButton* button = ButtonList.at(i);
        button->setRimShape(Folded);
        button->setGeometry(0,i*_h/ItemCount,_w,_h/ItemCount);
        if(!Folded && Current+ItemCount>Choices->size()&&Choices->size()>ItemCount)
            Current = Choices->size()-ItemCount;
        else if(!Folded && Choices->size()<ItemCount)
            Current = 0;
        int textNumber = i + Current;
        if(textNumber<Choices->size())
            button->setText(Choices->at(textNumber));

        if((!Folded||i==0)&&i<Choices->size())
            button->show();
        else
            button->hide();
        button->update();
    }
}

QString GameChooseBox::Value()
{
    if(Choices->size()==0)
        return "";
    return Choices->at(Current);
}

void GameChooseBox::Clicked(GameButton *button)
{
    int buttonNo = -1;
    for(int i=0;i<ItemCount;++i)
        if(ButtonList.at(i)==button)
        {
            buttonNo = i;
            break;
        }
    if(buttonNo==-1)
        return;
    setCurrent(Current+buttonNo);
    Folded = !Folded;
}

void GameChooseBox::setCurrent(int _No)
{
    if(_No<0)
        _No = 0;
    if(_No>=Choices->size())
        _No = Choices->size()-1;
    Current = _No;
}

void GameChooseBox::paintEvent(QPaintEvent *)
{
    ButtonsUpdate();
}

#include <QWheelEvent>
void GameChooseBox::wheelEvent(QWheelEvent *event)
{
    int offset = event->delta()/120;
    setCurrent(Current-offset);
}

void GameChooseBox::Add(const QString &_item)
{
    Choices->push_back(_item);
}

void GameChooseBox::setChoicesSource(QStringList *_source)
{
    Choices = _source;
}

void GameChooseBox::RemoveLastItem()
{
    Choices->pop_back();
}

void GameChooseBox::setFontSize(int px)
{
    for(int i=0;i<ItemCount;++i)
        ButtonList.at(i)->setFontSize(px);
}

int GameChooseBox::Count()
{
    return Choices->size();
}
