#ifndef SOMECHATMESSAGE_H
#define SOMECHATMESSAGE_H

#include <QObject>
#include "someMessage.h"

class someChatMessage : public someMessage
{
    Q_OBJECT
public:
    QString chatMessage;
    QString owner;
    someChatMessage(QObject* parent,const QString& _rawData);
    someChatMessage(QObject* parent,const QString& _chatMessage, const QString& _owner);
    virtual QString ToString();
    virtual void FromString(const QString &);
};

#endif // SOMECHATMESSAGE_H
