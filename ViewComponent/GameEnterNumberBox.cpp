#include "GameEnterNumberBox.h"
#include "mypainter.h"
#include <QKeyEvent>
#include <QDebug>

void GameEnterNumberBox::ContentButtonClicked(const QString &str)
{
    if(str=="bs")
    {
        if(!input.empty())
            input.pop_back();
    }
    else
    {
        char x = str.at(0).toLatin1();
        bool addable = false;
        if(x=='.')
        {
            if(input.size()==1)
                addable = true;
            else if(input.size()>1 && input.back()!='.')
                addable = true;
            int count = 0;
            for(int i=0;i<input.size();++i)
                if(input.at(i)=='.')
                    ++count;
            if(count>=3)
                addable = false;
        }
        else if(input.empty())
            addable = true;
        else
        {
            int num=0,multi=10;
            int i=1;
            while(i<=input.size()&&input.at(input.size()-i)!='.')
            {
                num += multi*(input.at(input.size()-i)-'0');
                multi*=10;
                ++i;
            }
            if(input.back()=='.')
                addable = true;
            else if(num+x-'0'<=255&&(num!=0))
                addable = true;
        }
        if(addable)
        {
            input.push_back(x);
            update();
        }
    }
}

void GameEnterNumberBox::Confirm()
{
    QString str = "";
    for(int i=0;i<input.size();++i)
        str += input.at(i);
    emit EmitIP(str);
}

void GameEnterNumberBox::paintEvent(QPaintEvent *event)
{
    GameViewPanel::paintEvent(event);
    MyPainter painter(this);
    int _w = this->width(), _h = this->height();
    inputbox->setGeometry(_w*0.15,_h*0.15,_w*0.7,_h*0.2);
    QFont font;
    font.setPixelSize(inputbox->height()*0.4);
    font.setFamily("Lucida Sans Unicode");
    inputbox->setFont(font);

    for(int i=0;i<10;++i)
        numberButton[i]->setGeometry(_w*(0.15+(i%5)*0.1),_h*(0.4+(i/5)*0.25),_w*0.08,_h*0.2);
    dotButton->setGeometry(_w*0.65,_h*0.4,_w*0.08,_h*0.2);
    delButton->setGeometry(_w*0.75,_h*0.4,_w*0.08,_h*0.2);
    OKButton->setGeometry(_w*0.65,_h*0.65,_w*0.18,_h*0.2);

    QString INPUT = "Enter IP: ";
    for(int i=0;i<input.size();++i)
        INPUT.append(input.at(i));
    inputbox->setText(INPUT);
    QPalette palette;
    palette.setBrush(QPalette::WindowText,Qt::white);
    inputbox->setPalette(palette);
}

void GameEnterNumberBox::keyPressEvent(QKeyEvent *event)
{
    int _key = event->key();
    if(_key>=Qt::Key_0 && _key<=Qt::Key_9)
    {
        ContentButtonClicked(QString::number(_key-Qt::Key_0));
        return;
    }
    switch(_key)
    {
    case Qt::Key_Backspace:
        ContentButtonClicked("bs");
        break;
    case Qt::Key_Period:
        ContentButtonClicked(".");
        break;
    case Qt::Key_Return:
        Confirm();
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

GameEnterNumberBox::GameEnterNumberBox(QWidget *parent):
    GameViewPanel(parent)
{
    this->setGeometry(parent->width()/4,parent->height()/3,parent->width()/2,parent->height()/3);
    mapper = new QSignalMapper(this);
    for(int i=0;i<10;++i)
    {
        numberButton[i] = new GameButton(QString::number(i),this);
        connect(numberButton[i],SIGNAL(Clicked()),mapper,SLOT(map()));
        mapper->setMapping(numberButton[i],QString::number(i));
    }
    dotButton = new GameButton(".",this);
    connect(dotButton,SIGNAL(Clicked()),mapper,SLOT(map()));
    mapper->setMapping(dotButton,".");

    delButton = new GameButton("del",this);
    connect(delButton,SIGNAL(Clicked()),mapper,SLOT(map()));
    mapper->setMapping(delButton,"bs");

    OKButton = new GameButton("OK",this);
    connect(OKButton,SIGNAL(Clicked()),this,SLOT(Confirm()));

    connect(mapper,SIGNAL(mapped(QString)),this,SLOT(ContentButtonClicked(QString)));

    inputbox = new QLabel("Enter IP:",this);
    inputbox->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);

    this->setFocusPolicy(Qt::StrongFocus);
}

