#include "someTimeCountMessage.h"

someTimeCountMessage::someTimeCountMessage(QObject *parent, const QString &_rawData):
    someMessage(parent,_rawData)
{
    MessageType="TIMECOUNT";
    FromString(_rawData);
}

someTimeCountMessage::someTimeCountMessage(QObject *parent, int _count):
    someMessage(parent),TimeCount(_count)
{
    MessageType="TIMECOUNT";
}

void someTimeCountMessage::FromString(const QString &_rawData)
{
    QString _RawData = _rawData.split("&",QString::SkipEmptyParts).at(0);
    QStringList strList = _RawData.split("%");
    if(strList.size()<2)
        return;
    TimeCount = strList.at(1).toInt();
}

QString someTimeCountMessage::ToString()
{
    QString str = "TIMECOUNT%"+QString::number(TimeCount)+"&";
    return str;
}
