#include "someCoordinateMessage.h"

someCoordinateMessage::someCoordinateMessage(QObject *parent, const QString &_rawData):
    someMessage(parent,_rawData)
{
    MessageType = "COORDINATE";
    FromString(_rawData);
}

someCoordinateMessage::someCoordinateMessage(QObject *parent, const QPoint &_data):
    someMessage(parent),data(_data)
{
    MessageType = "COORDINATE";
}

QString someCoordinateMessage::ToString()
{
    QString str = tr("COORDINATE%")+QString::number(data.x())+tr("%")+QString::number(data.y())+"&";
    return str;
}

void someCoordinateMessage::FromString(const QString &_rawData)
{
    QString _RawData = _rawData.split("&",QString::SkipEmptyParts).at(0);
    QStringList strList = _RawData.split("%");
    if(strList.size()<3)
        return;
    int _x = strList.at(1).toInt();
    int _y = strList.at(2).toInt();
    data = QPoint(_x,_y);
}


