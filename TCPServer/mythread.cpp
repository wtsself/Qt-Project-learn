#include "mythread.h"

myThread::myThread(QTcpSocket *s)
{
socket=s;
}

void myThread::run(){
    connect(socket, &QTcpSocket::readyRead,this,&myThread::clientInfoSlot);
}


//不能在其它类里使用ui界面，除非使用自定义信号
//每个对象有信号，可以自定义信号
void myThread::clientInfoSlot(){
     // qDebug()<<socket->readAll();
    QByteArray ba=socket->readAll();//读取的socket的数据为字节流对象
    emit sendToWidget(ba);//发送信号（带有数据），由Widget接受信号并处理

    //多线程处理事件后传信号到主线程中
}
