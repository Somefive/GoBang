#ifndef SOMEPLAINMESSAGE_H
#define SOMEPLAINMESSAGE_H

#include "someMessage.h"

class somePlainMessage : public someMessage
{
    Q_OBJECT

protected:



public:

    somePlainMessage(QObject* parent, QString _content);
    virtual void FromString(const QString &);
    virtual QString ToString();
    QString Content;

};

#endif // SOMEPLAINMESSAGE_H
