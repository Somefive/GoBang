#ifndef SOMEMESSAGECOMMUNICATOR_H
#define SOMEMESSAGECOMMUNICATOR_H

#include <QObject>
#include <QtNetwork>
#include <list>

using std::list;

#include "someMessage.h"
#include "someMessageManager.h"

class someMessageCommunicator : public QObject
{
    Q_OBJECT

protected:

    QTcpSocket* socket;

public:
    bool isServer;
    explicit someMessageCommunicator(QObject *parent = 0);
    static QString ServerAddress;
    static int ServerPort;
    bool IsConnect();
    static QString LocalIP();

signals:
    void GainMessage(someMessage*);
    void ConnectionEstablished();
    void ConnectionFailed(QAbstractSocket::SocketError);

public slots:
    virtual void FetchMessage();
    virtual void SendMessage(someMessage*);
    virtual void Connect(const QString& ip);
    virtual void ReLink();
};

#endif // SOMEMESSAGECOMMUNICATOR_H
