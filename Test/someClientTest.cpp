#include "someClientTest.h"
#include "ui_someClientTest.h"

someClientTest::someClientTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::someClientTest)
{
    ui->setupUi(this);
    client = new someMessageClient(this);
    connect(client,SIGNAL(GainMessage(someMessage*)),this,SLOT(GainMessage(someMessage*)));
}

someClientTest::~someClientTest()
{
    delete ui;
}

void someClientTest::GainMessage(someMessage *msg)
{
    somePlainMessage* pmsg = static_cast<somePlainMessage*>(msg);
    if(pmsg!=NULL)
    {
        ui->MsgBox->appendPlainText(pmsg->ToString());
    }
}

void someClientTest::SendMessage(someMessage *msg)
{
    client->SendMessage(msg);
}

void someClientTest::on_SendButton_clicked()
{
    QString text = ui->InputBox->toPlainText();
    somePlainMessage* pmsg = new somePlainMessage(0,text);
    SendMessage(pmsg);
}
