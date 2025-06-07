#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //模型类提供单独线程
    fsmodel=new QFileSystemModel(this);
    fsmodel->setRootPath(QDir::currentPath());//设置根目录
    //给视图指定模型对象
    /*注意QListView和QListWidget的区别是前者是可以自定义展示和编辑数据，而后者不能
    只能用其定义好的功能
*/
    ui->treeView->setModel(fsmodel);
    ui->listView->setModel(fsmodel);
    ui->tableView->setModel(fsmodel);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_listView_clicked(const QModelIndex &index)
{
    QStandardItemModel *model = new QStandardItemModel(this);

    QStandardItem *item1 = new QStandardItem("Item 1");
    QStandardItem *item2 = new QStandardItem("Item 2");
    model->appendRow(item1);
    model->appendRow(item2);
    ui->listView->setModel(model);

}
