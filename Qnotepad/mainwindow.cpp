#include "mainwindow.h"
#include "ui_mainwindow.h"

//Qt中还有一个比较重要的机制是事件机制
//有很多种不同的事件（鼠标事件，键盘事件，拖拽事件，滚动事件...），都继承抽象类QEvent
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //mainwindow项目相对于widget多了菜单这一功能
    //菜单功能有三级:meunbar->meun->action
    //菜单栏->菜单->菜单项(行为)
    connect(ui->action_N,&QAction::triggered,this,&MainWindow::newActionSlot);
    connect(ui->action_O,&QAction::triggered,this,&MainWindow::openActionSlot);
    connect(ui->action_S,&QAction::triggered,this,&MainWindow::saveActionSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//新建窗口
void MainWindow::newActionSlot(){
    ui->textEdit->clear();
    this->setWindowTitle("新建文本文档.txt");

}

//打开文件窗口
void MainWindow::openActionSlot(){
    //调用相应函数让其跳出窗口
    //该静态函数会返回一个文件名
    //四个参数，第一个参数表示展示在哪个父类对象下展示，第二个为菜单名，第三个为初始的展示文件路径，第四个为展示的类型
    //这里的第三个参数的意思是在当前路径
    QString filename=QFileDialog::getOpenFileName(this,"选择一个文件",
                                                  QCoreApplication::applicationFilePath(),"*.cpp");
    if(filename.isEmpty()){
        QMessageBox::warning(this,"警告","请选择一个文件");
    }
    else{
        //打印文件路径
        qDebug()<<"文件filename为："<<filename;
        //创建文件对象
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        //Qt的QByteArray类提供了很方便的对字节流操作的接口,QByteArray没有继承任何Qt基类。
        //Qt的QString类提供了很方便的对字符串操作的接口，QString没有继承任何Qt基类。
        //​QString是专门用来处理字符串的，除了能处理ASCII编码字符，还包括各国语言的编码，默认情况下QString会把所有数据当做utf-8编码来处理
        //QByteArray只是单纯用来处理数据的，除了能处理ASCII编码字符，其它复杂的编码不能处理，直接以字节流的方式来对待。
        QByteArray ba=file.readAll();
        ui->textEdit->setText(QString(ba));

        file.close();
    }
}

//另存为窗口
void MainWindow::saveActionSlot(){

    QString filename=QFileDialog::getSaveFileName(this,"选择一个文件",
                                                  QCoreApplication::applicationFilePath());
    if(filename.isEmpty()){
        QMessageBox::warning(this,"警告","请选择一个文件");
    }
    else{
        QFile file(filename);
        file.open(QIODevice::WriteOnly);
        QByteArray ba;
        //以纯文本的方式传入字节流
        ba.append( ui->textEdit->toPlainText());
        file.write(ba);
        file.close();
    }
};

//保存快捷键设置
void MainWindow::keyPressEvent(QKeyEvent* k){
    //设置对应的键盘事件Ctrl+S
    if(k->modifiers()==Qt::ControlModifier&& k->key()==Qt::Key_S){
        saveActionSlot();
    }
};

void MainWindow::mousePressEvent(QMouseEvent *m){
    //获取鼠标位置
    QPoint d=m->pos();
    qDebug()<<d;
    //获取鼠标的左右键
    if(m->button()==Qt::LeftButton){
        qDebug()<<"左键被按下 ";
    }
    else if(m->button()==Qt::RightButton){
        qDebug()<<"右键被按下";
    }

}









