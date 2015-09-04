#include "someNotifyMessage.h"

using namespace someMessageManager;

someNotifyMessage::someNotifyMessage(QObject *parent, const QString &_rawData):
    someMessage(parent,_rawData)
{
    MessageType="NOTIFY";
    FromString(_rawData);
}

someNotifyMessage::someNotifyMessage(QObject *parent, NOTIFYTYPE _type):
    someMessage(parent),NotifyType(_type)
{
    MessageType="NOTIFY";
}

void someNotifyMessage::FromString(const QString &_rawData)
{
    QString _RawData = _rawData.split("&",QString::SkipEmptyParts).at(0);
    QStringList strList = _RawData.split("%");
    if(strList.size()<2)
        return;
    NotifyType = getNotifyType(strList.at(1));
}

QString someNotifyMessage::ToString()
{
    QString str = "NOTIFY%"+someMessageManager::ToString(NotifyType)+"&";
    return str;
}
