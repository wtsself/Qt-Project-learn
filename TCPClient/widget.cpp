#include "widget.h"
#include "ui_widget.h"
#include<QMessageBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //创建socket对象
    socket=new QTcpSocket;
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_cancel_btn_clicked()
{
    this->close();
}

void Widget::on_connect_btn_clicked()
{

    //获取ip地址和端口号
    QString IP=ui->address->text();
    QString port=ui->port->text();
     //连接服务器
    socket->connectToHost(QHostAddress(IP),port.toUShort());

    //连接成功，发出信号
    connect(socket,&QTcpSocket::connected,[this]()
    {
        QMessageBox::information(this,"connect tip","connect success");
        //可以 选择隐藏或关闭旧的窗口
        this->hide();
        Chat *c=new Chat(socket);//这里是把新窗口对象放在堆区，避免被当局部变量释放
        //在传入socket时要修改构造函数
        c->show();



});

    //连接失败，发出信号
    connect(socket,&QTcpSocket::disconnected,[this]()
    {
        QMessageBox::warning(this,"connect tip","connect faied");
});


}
