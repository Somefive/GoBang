#ifndef SOMESERVERTEST_H
#define SOMESERVERTEST_H

#include <QWidget>
#include "Message/someMessageServer.h"
#include "Message/someMessage.h"
#include "Message/somePlainMessage.h"

namespace Ui {
class someServerTest;
}

class someServerTest : public QWidget
{
    Q_OBJECT

public:
    explicit someServerTest(QWidget *parent = 0);
    ~someServerTest();

private:
    Ui::someServerTest *ui;
    someMessageServer* server;
public slots:
    void DisplayMessage(someMessage*);
protected slots:
    void GainMessage(someMessage*);
    void SendMessage(someMessage*);

private slots:
    void on_SendBtn_clicked();
};

#endif // SOMESERVERTEST_H
