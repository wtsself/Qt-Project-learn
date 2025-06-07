#include <QApplication>
#include <QLabel>
#include<QLineEdit>
#include<QWidget>
#include<QPushButton>
#include<QHBoxLayout>//水平布局
#include<QVBoxLayout>//垂直布局

int main(int argc, char *argv[])
{
    //事件系统，只能有一个，用于处理事件
    QApplication app(argc, argv);

    //定义了两个标签，一个行编辑，三个按钮
    QLabel *infolabel=new QLabel();
    QLabel *openlabel=new QLabel();
    QLineEdit *eidt=new QLineEdit();
    QPushButton *btn1=new QPushButton();
    QPushButton *btn2=new QPushButton();
    QPushButton *btn3=new QPushButton();

    //设置组件文本内容
    infolabel->setText("input cmd:");
    openlabel->setText("open:");

    btn1->setText("commit");
    btn2->setText("cancel");
    btn3->setText("browse");

    //创造水平布局对象，用于指定组件的分布
    QHBoxLayout *cmdline=new QHBoxLayout();
    cmdline->addWidget(openlabel);
    cmdline->addWidget(eidt);


    QHBoxLayout *btnline=new QHBoxLayout();
    btnline->addWidget(btn1);
    btnline->addWidget(btn2);
    btnline->addWidget(btn3);

    //垂直布局，内可包含水平布局对象,注意添加组件对象是addwidget，添加布局对象是addlayout
    QVBoxLayout *vet=new QVBoxLayout();
    vet->addWidget(infolabel);
    vet->addLayout(cmdline);
    vet->addLayout(btnline);

    //创建Q组件对象使用自定义的布局（最高级的布局，等同于HTML的html标签一样）
    QWidget w;
    w.setLayout(vet);
    w.show();
    w.setWindowTitle("running");



    //开启事件循环
    return app.exec();
}
