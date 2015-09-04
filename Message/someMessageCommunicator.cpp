#include "someMessageCommunicator.h"
#include "someMessage.h"
#include "somePlainMessage.h"

#include <QDebug>
#include <vector>

using std::vector;

someMessageCommunicator::someMessageCommunicator(QObject *parent) :
    QObject(parent),socket(NULL)
{
}

void someMessageCommunicator::SendMessage(someMessage *msg)
{
    if(!IsConnect())
        return;
    QByteArray array;
    array.clear();
    QString info = msg->ToString();
    array.append(info);
    socket->write(array);
    qDebug()<<"SendMessage:"<<msg->ToString();
}

void someMessageCommunicator::Connect(const QString &ip)
{

}

void someMessageCommunicator::FetchMessage()
{
    if(IsConnect())
    {
        QString rawData = socket->readAll();
        vector<someMessage*> msgs = someMessageManager::GetMessage(rawData);
        for(int i=0;i<msgs.size();++i)
        {
            someMessage* msg = msgs.at(i);
            qDebug()<<"Gain Message:"<<msg->ToString();
            emit GainMessage(msg);
        }
    }
}

bool someMessageCommunicator::IsConnect()
{
    if(socket==NULL)
        return false;
    return socket->state()==QAbstractSocket::ConnectedState;
}

QString someMessageCommunicator::LocalIP()
{
    QString localHostName = QHostInfo::localHostName();
    QHostInfo hostInfo = QHostInfo::fromName(localHostName);
    QList<QHostAddress> addresses = hostInfo.addresses();
    for(int i=0;i<addresses.size();++i)
    {
        QHostAddress adr = addresses.at(i);
        if(adr.protocol()==QAbstractSocket::IPv4Protocol)
            return adr.toString();
    }
    return "";
}

void someMessageCommunicator::ReLink()
{

}

QString someMessageCommunicator::ServerAddress = "127.0.0.1";
int someMessageCommunicator::ServerPort = 8080;
