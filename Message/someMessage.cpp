#include "someMessage.h"

someMessage::someMessage(QObject *parent):
    QObject(parent)
{

}

someMessage::someMessage(QObject *parent, const QString &_rawData):
    QObject(parent)
{
    this->FromString(_rawData);
}

void someMessage::FromString(const QString &)
{

}

