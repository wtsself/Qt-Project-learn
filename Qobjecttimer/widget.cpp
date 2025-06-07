#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("图片放映器");
    picId=1;
    //在lable标签中展示初始图片，用的Qpixmap对象
    QPixmap pix("D:\\qt-pro\\static\\img\\0.jpg");
    //往对应标签传入图片对象
    ui->piclabel->setPixmap(pix);




}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_startbutton_clicked()
{
    //开启Qobject定时器，返回定时器编号，用以定位定时器
     myTimerId=this->startTimer((TIMEOUT));
}

void Widget::timerEvent(QTimerEvent *event){

    if(event->timerId()!=myTimerId)
        return ;
    //拼凑自动展示的图片路径,注意该路径不能包含空格
    QString path("D:\\qt-pro\\static\\img\\");
    //下面是把picId的类型从number改为string
    path+=QString::number(picId);
    path+=".jpg";
    QPixmap pix(path);
    ui->piclabel->setPixmap(pix);
    picId=(picId%5)+1;



};

void Widget::on_stopbutton_clicked()
{
    //杀死对应定时器
    this->killTimer(myTimerId);
}
