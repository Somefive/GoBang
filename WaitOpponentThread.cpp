#include "WaitOpponentThread.h"

void WaitOpponentThread::run()
{
    while(answer!=0)
    {
        this->sleep(500);
    }
}

WaitOpponentThread::WaitOpponentThread(QObject *parent, int *_answer):
    QThread(parent),answer(_answer)
{

}



