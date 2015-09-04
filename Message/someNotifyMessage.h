#ifndef SOMENOTIFYMESSAGE_H
#define SOMENOTIFYMESSAGE_H

#include <QObject>
#include "someMessage.h"
#include "someMessageManager.h"

class someNotifyMessage : public someMessage
{
    Q_OBJECT
public:
    someMessageManager::NOTIFYTYPE NotifyType;
    someNotifyMessage(QObject*,const QString&);
    someNotifyMessage(QObject*,someMessageManager::NOTIFYTYPE);
    virtual void FromString(const QString &);
    virtual QString ToString();
};

#endif // SOMENOTIFYMESSAGE_H
