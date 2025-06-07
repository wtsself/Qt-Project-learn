#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("图片放映器");
    picId=1;
    qtime=new QTimer;
    QImage img;
    img.load("D:\\qt-pro\\static\\img\\0.jpg");
    ui->label->setPixmap(QPixmap::fromImage(img));
    //定时器到时间，发出timeout信号
    connect(qtime,&QTimer::timeout,this,&Widget::timeoutslot);
}
Widget::~Widget()
{
    delete ui;
}
void Widget::on_startbtn_clicked()
{
    //每1000ms触发一次函数，该函数需要自己来实现
    qtime->start(TIMEOUT);
}

void Widget::on_stopbtn_clicked()
{
    qtime->stop();
}
void Widget::timeoutslot(){

    QString path("D:\\qt-pro\\static\\img\\");
      //下面是把picId的类型从number改为string
      path+=QString::number(picId);
      path+=".jpg";
      QImage img;
      img.load(path);
      ui->label->setPixmap(QPixmap::fromImage(img));
      picId=(picId%5)+1;
}
//这里体现了QTimer的特别之处，可以限定定时器的使用次数
void Widget::on_nextbtn_clicked()
{
    QTimer::singleShot(1,this,SLOT(timeoutslot()));
}
