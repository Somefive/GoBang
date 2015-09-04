#ifndef WAITOPPONENTTHREAD_H
#define WAITOPPONENTTHREAD_H

#include <QObject>
#include <QThread>

class WaitOpponentThread : public QThread
{
    Q_OBJECT
protected:
    virtual void run() Q_DECL_OVERRIDE;

public:
    int* answer;
    WaitOpponentThread(QObject *parent, int *_answer);
};

#endif // WAITOPPONENTTHREAD_H
