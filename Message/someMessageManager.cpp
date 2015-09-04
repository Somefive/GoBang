#include "someMessageManager.h"
#include "someCoordinateMessage.h"
#include "someNotifyMessage.h"
#include "someTimeCountMessage.h"
#include "somePlainMessage.h"
#include "someLoadMessage.h"
#include "someChatMessage.h"
#include <QDebug>


using namespace someMessageManager;

vector<someMessage *> someMessageManager::GetMessage(const QString &_rawData)
{
    qDebug()<<"MessageManager GetMessage:"<<_rawData;
    vector<someMessage*> msgList;
    QStringList rawDataList = _rawData.split("&",QString::SkipEmptyParts);
    for(int i=0;i<rawDataList.size();++i)
    {
        QString rawMsg = rawDataList.at(i);
        QStringList rawMsgList = rawMsg.split("%");
        QString rtype = rawMsgList[0];
        TYPE type = getType(rtype);
        someMessage* msg;
        switch(type)
        {
        case COORDINATE:
            msg = new someCoordinateMessage(0,rawMsg);
            break;
        case NOTIFY:
            msg = new someNotifyMessage(0,rawMsg);
            break;
        case TIMECOUNT:
            msg = new someTimeCountMessage(0,rawMsg);
            break;
        case LOAD:
            msg = new someLoadMessage(0,rawMsg);
            break;
        case CHAT:
            msg = new someChatMessage(0,rawMsg);
            break;
        default:
            msg = new somePlainMessage(0,rawMsg);
            break;
        }
        qDebug()<<"Manager Generate Message:"<<msg->ToString();
        msgList.push_back(msg);
    }
    return msgList;
}

someMessageManager::TYPE someMessageManager::getType(const QString &type)
{
    if(type=="COORDINATE")
        return COORDINATE;
    if(type=="TIMECOUNT")
        return TIMECOUNT;
    if(type=="NOTIFY")
        return NOTIFY;
    if(type=="LOAD")
        return LOAD;
    if(type=="CHAT")
        return CHAT;
    return PLAIN;
}



QString someMessageManager::ToString(TYPE type)
{
    switch(type)
    {
    case COORDINATE:
        return "COORDINATE";
    case TIMECOUNT:
        return "TIMECOUNT";
    case NOTIFY:
        return "NOTIFY";
    case LOAD:
        return "LOAD";
    case CHAT:
        return "CHAT";
    default:
        return "PLAIN";
    }
}


someMessageManager::NOTIFYTYPE someMessageManager::getNotifyType(const QString &type)
{
    if(type=="TIMEOUT")
        return TIMEOUT;
    if(type=="UNDO")
        return UNDO;
    if(type=="QUIT")
        return QUIT;
    if(type=="YES")
        return YES;
    if(type=="NO")
        return NO;
    if(type=="QLOAD")
        return QLOAD;
    else
        return NONE;
}



QString someMessageManager::ToString(NOTIFYTYPE type)
{
    switch(type)
    {
    case TIMEOUT:
        return "TIMEOUT";
    case UNDO:
        return "UNDO";
    case QUIT:
        return "QUIT";
    case YES:
        return "YES";
    case NO:
        return "NO";
    case QLOAD:
        return "QLOAD";
    default:
        return "NONE";
    }
}
