#include "someChatMessage.h"

someChatMessage::someChatMessage(QObject *parent, const QString &_rawData):
    someMessage(parent)
{
    MessageType = "CHAT";
    FromString(_rawData);
}

someChatMessage::someChatMessage(QObject *parent, const QString &_chatMessage, const QString &_owner):
    someMessage(parent),chatMessage(_chatMessage),owner(_owner)
{
    MessageType = "CHAT";
}

QString someChatMessage::ToString()
{
    QString str = "CHAT%" + chatMessage + "%" + owner + "&";
    return str;
}

void someChatMessage::FromString(const QString &_rawData)
{
    QString _RawData = _rawData.split("&",QString::SkipEmptyParts).at(0);
    QStringList strList = _RawData.split("%");
    if(strList.size()<3)
        return;
    chatMessage =  strList.at(1);
    owner = strList.at(2);
}
