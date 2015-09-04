#ifndef SOMEMESSAGECLIENT_H
#define SOMEMESSAGECLIENT_H

#include "someMessageCommunicator.h"


class someMessageClient: public someMessageCommunicator
{

    Q_OBJECT

public:

    someMessageClient(QObject* parent);
    virtual void ReLink();
public slots:
    virtual void Connect(const QString& ip);
private slots:
};

#endif // SOMEMESSAGECLIENT_H
