#include "widget.h"
#include "ui_widget.h"
#include<QProcess>
#include<QLineEdit>
#include<QString>
#include<QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //connect函数连接信号与槽，有四个参数，分别是1：谁发出信号，2：发出什么信号，3：谁处理信号，4：怎么处理信号
    //有两种普通格式，一种是宏定义，一种是取地址
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(on_btn1_clicked()));
    connect(ui->btn2,&QPushButton::clicked,this,&Widget::on_btn2_clicked);
    //还有一种lambda表达式的格式，在函数功能比较简单的情况下
    connect(ui->btn3,&QPushButton::clicked,[this]()
    {
        QMessageBox::information(this,"信息","点击浏览");
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btn1_clicked()
{
    //获取行编辑对象的内容
    QString program=ui->lineEdit->text();
    //创建一个进程对象,并在启动时传入值
    QProcess *process=new QProcess(this);
    process->start(program);
}

void Widget::on_btn2_clicked()
{
    this->close();
}
