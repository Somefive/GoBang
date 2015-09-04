#include "somePlainMessage.h"

somePlainMessage::somePlainMessage(QObject *parent, QString _content):
    someMessage(parent),Content(_content)
{
    MessageType = "PLAIN";
}

void somePlainMessage::FromString(const QString &_rawData)
{
    Content = _rawData;
}

QString somePlainMessage::ToString()
{
    return Content;
}

