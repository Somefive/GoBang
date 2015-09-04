#include "someMessageServer.h"
#include <QDebug>

someMessageServer::someMessageServer(QObject *parent):
    someMessageCommunicator(parent)
{
    isServer = true;
    server = new QTcpServer(this);
    server->listen(QHostAddress::Any,ServerPort);
    connect(server,SIGNAL(newConnection()),this,SLOT(AcceptConnection()));
    connect(server,SIGNAL(acceptError(QAbstractSocket::SocketError)),this,SIGNAL(ConnectionFailed(QAbstractSocket::SocketError)));
}

void someMessageServer::ReLink()
{
    if(socket!=NULL)
    {
        socket->close();
        delete socket;
        socket = NULL;
    }
}

void someMessageServer::AcceptConnection()
{
    if(socket!=NULL)
        return;
    QTcpSocket* newSocket = server->nextPendingConnection();
    connect(newSocket,SIGNAL(readyRead()),this,SLOT(FetchMessage()));
    connect(newSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SIGNAL(ConnectionFailed(QAbstractSocket::SocketError)));
    socket = newSocket;
    emit ConnectionEstablished();
}
