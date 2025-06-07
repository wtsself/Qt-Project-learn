#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->tableView->setVisible(false);//先把表框隐藏，在点击查询后再显示
    //连接数据库
    db=QSqlDatabase::addDatabase("QMYSQL"); //加载数据库驱动
    //这里是我按照CSDN上的教程重新打了驱动，但是只在mingw32的编译器中打了，同样也可以在msvc中打（msvc中没动），基本就是一个动态库文件和两个驱动文件

    //初始化数据库
    db.setDatabaseName("mydatabase");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("123456");
    if(db.open()){
        QMessageBox::information(this,"数据库连接提示","连接成功");

    }
    else{
        QMessageBox::warning(this,"数据库连接提示","连接失败");
    }


}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_insert_clicked()
{
    QString id=ui->id_line->text();
    QString name=ui->name_line->text();
    QString birth =ui->birth_line->text();

    //用sql语句插入,这里使用了QString的按次序占位插入的方法
    QString sql=QString("insert into student values (%1,'%2','%3');").arg(id).arg(name).arg(birth);
    //创建查询对象
    QSqlQuery query;
    if(query.exec(sql)){
            QMessageBox::information(this,"数据插入提示","插入成功");
        }
        else{
            QMessageBox::warning(this,"数据插入提示","插入失败");
        }

}

void Widget::on_shearch_clicked()
{
    //创建表模型来展示数据
    //创建sql表模型，与表关联，然后将模型与tableview组件关联
    m=new QSqlTableModel;
    m->setTable("student");
    ui->tableView->setModel(m);
    ui->tableView->setVisible(true);

    QSqlQuery query;
    query.exec("select * from student;");
    //一次只能查询一个，所以要循环next
    while (query.next()) {
        qDebug()<<query.value(0);
         qDebug()<<query.value(1);
          qDebug()<<query.value(2);
    }

    m->select();

}
