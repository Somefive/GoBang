#include "someMessageClient.h"
#include <QDebug>

someMessageClient::someMessageClient(QObject *parent):
    someMessageCommunicator(parent)
{
    isServer = false;
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(connected()),this,SIGNAL(ConnectionEstablished()));
}

void someMessageClient::ReLink()
{
    if(IsConnect())
        socket->disconnected();
    socket->connectToHost(QHostAddress(ServerAddress),ServerPort);
    qDebug()<<"ReLink with state:"<<socket->state();
}

void someMessageClient::Connect(const QString &ip)
{
    ServerAddress = ip;
    socket->connectToHost(ServerAddress,ServerPort);
    connect(socket,SIGNAL(readyRead()),this,SLOT(FetchMessage()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SIGNAL(ConnectionFailed(QAbstractSocket::SocketError)));
}

