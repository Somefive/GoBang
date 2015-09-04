#include "someLoadMessage.h"



someLoadMessage::someLoadMessage(QObject *parent, const QString& _rawData):
    someMessage(parent,_rawData)
{
    MessageType = "LOAD";
    FromString(_rawData);
}

someLoadMessage::someLoadMessage(QObject *parent, const QString &_map, const QChar &_turn):
    someMessage(parent),Map(_map),Turn(_turn)
{
    MessageType = "LOAD";
}

QString someLoadMessage::ToString()
{
    QString str = "LOAD%"+Map+"%"+Turn+"&";
    return str;
}

void someLoadMessage::FromString(const QString &_rawData)
{
    QString _RawData = _rawData.split("&",QString::SkipEmptyParts).at(0);
    QStringList strList = _RawData.split("%");
    if(strList.size()<3)
        return;
    Map = strList.at(1);
    Turn = strList.at(2).at(0);
}
