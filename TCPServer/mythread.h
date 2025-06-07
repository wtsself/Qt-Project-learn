#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include<QThread>
#include <QTcpSocket>
#include <QDebug>
//自定义的线程类，重写run函数，处理服务器传来的任务，接受数据并执行
class myThread :  public QThread
{
    Q_OBJECT//这个宏定义跟信号与槽有关系
public:
    explicit myThread(QTcpSocket *s);
    void run();//重写QThread中的run函数，线程处理函数



signals:
    void sendToWidget(QByteArray b );


private slots:
    void clientInfoSlot();
private:

       QTcpSocket *socket;
};

#endif // MYTHREAD_H
