#include "chat.h"
#include "ui_chat.h"

Chat::Chat(QTcpSocket *s,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{

    ui->setupUi(this);
    socket=s;
}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_cancel_btn_clicked()
{
    ui->send_edit->clear();
}

void Chat::on_send_btn_clicked()
{
    //先获取，后发送
    QByteArray ba;
    //使用ui获取的是QString类型，要转为QByterray的类型才能传入socket
    ba.append(ui->send_edit->toPlainText());
    socket->write(ba);
}
