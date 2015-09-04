#ifndef SOMECLIENTTEST_H
#define SOMECLIENTTEST_H

#include <QWidget>
#include "Message/someMessageClient.h"
#include "Message/someMessage.h"
#include "Message/somePlainMessage.h"

namespace Ui {
class someClientTest;
}

class someClientTest : public QWidget
{
    Q_OBJECT

public:
    explicit someClientTest(QWidget *parent = 0);
    ~someClientTest();

private:
    Ui::someClientTest *ui;
    someMessageClient* client;

private slots:
    void GainMessage(someMessage*);
    void SendMessage(someMessage*);
    void on_SendButton_clicked();
};

#endif // SOMECLIENTTEST_H
