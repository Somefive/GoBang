#ifndef SOMETIMECOUNTMESSAGE_H
#define SOMETIMECOUNTMESSAGE_H

#include <QObject>
#include "someMessage.h"

class someTimeCountMessage : public someMessage
{
    Q_OBJECT
public:
    int TimeCount;
    someTimeCountMessage(QObject*,const QString&);
    someTimeCountMessage(QObject*,int _count);
    virtual void FromString(const QString &);
    virtual QString ToString();
};

#endif // SOMETIMECOUNTMESSAGE_H
