#include "someServerTest.h"
#include "ui_someServerTest.h"

someServerTest::someServerTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::someServerTest)
{
    ui->setupUi(this);
    server = new someMessageServer(this);
    connect(server,SIGNAL(GainMessage(someMessage*)),this,SLOT(GainMessage(someMessage*)));
}

someServerTest::~someServerTest()
{
    delete ui;
}

void someServerTest::GainMessage(someMessage *msg)
{
    DisplayMessage(msg);
}

void someServerTest::SendMessage(someMessage *msg)
{
    server->SendMessage(msg);
}

void someServerTest::DisplayMessage(someMessage *msg)
{
    somePlainMessage* pmsg = static_cast<somePlainMessage*>(msg);
    if(pmsg!=NULL)
    {
        ui->MsgBox->append(pmsg->Content);
    }
}



void someServerTest::on_SendBtn_clicked()
{
    QString text = ui->InputBox->toPlainText();
    somePlainMessage* pmsg = new somePlainMessage(0,text);
    SendMessage(pmsg);
}
