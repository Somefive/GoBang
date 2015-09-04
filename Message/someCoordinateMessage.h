#ifndef SOMECOORDINATEMESSAGE_H
#define SOMECOORDINATEMESSAGE_H

#include "someMessage.h"
#include <QPoint>

class someCoordinateMessage : public someMessage
{
    Q_OBJECT

public:
    QPoint data;
    someCoordinateMessage(QObject* parent,const QString& _rawData);
    someCoordinateMessage(QObject* parent,const QPoint& _data);
    virtual QString ToString();
    virtual void FromString(const QString &);
};

#endif // SOMECOORDINATEMESSAGE_H
