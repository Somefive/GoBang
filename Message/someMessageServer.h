#ifndef SOMEMESSAGESERVER_H
#define SOMEMESSAGESERVER_H

#include <list>
#include <QSignalMapper>

#include "someMessageCommunicator.h"

using std::list;

class someMessageServer: public someMessageCommunicator
{
    Q_OBJECT

signals:

protected slots:

    void AcceptConnection();

protected:

    QTcpServer* server;

public:

    someMessageServer(QObject* parent);
    virtual void ReLink();
};

#endif // SOMEMESSAGESERVER_H
