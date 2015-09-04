#ifndef SOMELOADMESSAGE_H
#define SOMELOADMESSAGE_H

#include <QObject>
#include "someMessage.h"

class someLoadMessage : public someMessage
{
    Q_OBJECT
public:
    QString Map;
    QChar Turn;
    someLoadMessage(QObject* parent,const QString& _rawData);
    someLoadMessage(QObject* parent,const QString& _map, const QChar& _turn);
    virtual QString ToString();
    virtual void FromString(const QString &);
};

#endif // SOMELOADMESSAGE_H
