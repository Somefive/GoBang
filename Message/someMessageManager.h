#ifndef SOMEMESSAGEMANAGER_H
#define SOMEMESSAGEMANAGER_H

#include <QObject>
#include "someMessage.h"

#include <vector>

using std::vector;


namespace someMessageManager
{
    vector<someMessage*> GetMessage(const QString&);
    enum TYPE{NOTIFY,COORDINATE,TIMECOUNT,PLAIN,LOAD,CHAT};
    TYPE getType(const QString&);
    QString ToString(TYPE);
    enum NOTIFYTYPE{TIMEOUT,UNDO,QUIT,NONE,YES,NO,QLOAD};
    NOTIFYTYPE getNotifyType(const QString&);
    QString ToString(NOTIFYTYPE);
}


#endif // SOMEMESSAGEMANAGER_H
