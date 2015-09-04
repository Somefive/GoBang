#include "GameLoadFilePanel.h"
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>
#include "gamemessagebox.h"
void GameLoadFilePanel::paintEvent(QPaintEvent *event)
{
    int w = width(), h = height();
    Title->setGeometry(0,h*0.1,w,h*0.17);
    ChooseBox->setGeometry(w*0.2,h*0.3,w*0.6,h*0.5);
    ChooseButton->setGeometry(w*0.2,h*0.82,w*0.25,h*0.08);
    CancelButton->setGeometry(w*0.55,h*0.82,w*0.25,h*0.08);
    GameViewPanel::paintEvent(event);
}

GameLoadFilePanel::GameLoadFilePanel(QWidget *parent):
    GameViewPanel(parent)
{
    Title = new QLabel("Please Choose Your File",this);
    QPalette palette;
    palette.setBrush(QPalette::WindowText,Qt::white);
    Title->setPalette(palette);
    Title->setFont(QFont("Century Gothic",16));
    Title->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    ChooseButton = new GameButton("Choose",this);
    CancelButton = new GameButton("Cancel",this);

    ChooseBox = new GameChooseBox(this,4);

    QDir rootDir(QCoreApplication::applicationDirPath()+"/Resources/Data");
    QStringList namefilter;
    namefilter<<"*.txt";
    QFileInfoList fiList = rootDir.entryInfoList(namefilter);
    for(unsigned int i=0;i<fiList.size();++i)
    {
        QFileInfo fi = fiList.at(i);
        ChooseBox->Add(fi.fileName());
    }

    if(ChooseBox->Count()<=0)
    {
        hide();
        GameMessageBox* msgBox = new GameMessageBox(parent,"Warning!","Cannot Find Any File.","OK");
        msgBox->show();
        connect(msgBox,SIGNAL(CentralButtonClicked()),msgBox,SLOT(hide()));
        connect(msgBox,SIGNAL(CentralButtonClicked()),msgBox,SLOT(deleteLater()));
        deleteLater();
    }

    connect(ChooseButton,SIGNAL(Clicked()),this,SLOT(ChooseButtonClicked()));
    connect(ChooseButton,SIGNAL(Clicked()),this,SLOT(hide()));
    connect(ChooseButton,SIGNAL(Clicked()),this,SLOT(deleteLater()));
    connect(CancelButton,SIGNAL(Clicked()),this,SLOT(hide()));
    connect(CancelButton,SIGNAL(Clicked()),this,SLOT(deleteLater()));
}

void GameLoadFilePanel::ChooseButtonClicked()
{
    qDebug()<<"Choose"+ChooseBox->Value();
    if(ChooseBox->Value()!="")
        emit ChooseLoadFile(ChooseBox->Value());
}
