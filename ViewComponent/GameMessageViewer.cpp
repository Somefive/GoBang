#include "GameMessageViewer.h"

void GameMessageViewer::paintEvent(QPaintEvent *event)
{
    GameViewPanel::paintEvent(event);
    int w = width(), h = height();
    textViewer->setGeometry(w*0.05,h*0.1,w*0.9,h*0.8);
    QString viewText = "";
    for(int i=0;i<texts.size();++i)
        viewText += texts.at(i)+"\n";
    textViewer->setText(viewText);
    textViewer->setWordWrap(true);
    textViewer->setAlignment(Qt::AlignLeft|Qt::AlignTop);
}

GameMessageViewer::GameMessageViewer(QWidget *parent):
    GameViewPanel(parent),MaxTextNumber(4)
{
    int w = parent->width(), h = parent->height();
    this->setGeometry(w*0.05,h*0.21,w*0.3,h*0.38);
    textViewer = new QLabel(this);
    QPalette palette;
    palette.setBrush(QPalette::WindowText,Qt::white);
    textViewer->setPalette(palette);
    textViewer->setFont(QFont("Comic Sans MS",12));
}

void GameMessageViewer::AddText(const QString &_addText)
{
    if(texts.size()>=MaxTextNumber)
        texts.pop_front();
    texts.push_back(_addText);
    update();
}

void GameMessageViewer::Clear()
{
    texts.clear();
}

