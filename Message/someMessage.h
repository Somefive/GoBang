#ifndef SOMEMESSAGE_H
#define SOMEMESSAGE_H

#include <QObject>

class someMessage : public QObject
{
    Q_OBJECT

public:
    someMessage(QObject *parent);
    someMessage(QObject *parent, const QString&);
    virtual QString ToString() =0;
    virtual void FromString(const QString&) ;
    QString MessageType;

signals:

public slots:

};

#endif // SOMEMESSAGE_H
