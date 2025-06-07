#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    server=new QTcpServer;
    //监听,第一个参数为网关类型，第二个为端口号
    server->listen(QHostAddress::AnyIPv4,8000);

    //客户端发起连接，server发出信号
    connect(server,&QTcpServer::newConnection,this,&Widget::newClientHandler);
}

Widget::~Widget()
{
    delete ui;
}

//客户段发送的信息处理函数
void Widget::newClientHandler(){
    //建立TCP连接
    QTcpSocket *socket=server->nextPendingConnection();
    //socket->peerAddress();//获取客户端ip地址
    //socket->peerPort();//获取客户端端口
    ui->address->setText(socket->peerAddress().toString());
    ui->port->setText(QString::number(socket->peerPort()));

    //服务器接受客户端发送的信息，socket发出readyread信号
    //connect(socket,&QTcpSocket::readyRead,this,&Widget::newClientInfo);

    //多线程操作
    //启动线程
    myThread *t=new myThread(socket);//创建线程对象
    t->start();//Qt的线程类中的函数，启动线程
    //接收线程传来的信号，并在ui中显示
    connect(t,&myThread::sendToWidget,this,&Widget::threadSlot);

}

//void Widget::newClientInfo(){
//    //获取信号发出者，对应的是connet的第一个参数谁发出信号
//    QTcpSocket *s=(QTcpSocket *)sender();
//    //注意，将QString转为QByteArray时用：
//    //QByteArray ba;
//    //ba.append(QString的内容);
//    //而将QByteArray转为QString时则要用：
//    //QString(QByteArray的内容);

//    ui->show->setText(QString( s->readAll()));


//}

void Widget::threadSlot(QByteArray b){
    ui->show->setText(QString(b));
}








