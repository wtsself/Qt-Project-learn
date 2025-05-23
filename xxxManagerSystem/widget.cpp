#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initnavBarTreeWidget();

}

Widget::~Widget()
{
    delete ui;
}

void Widget:: work(int id,QString pwd){

this->show();
    qDebug()<<"页面跳转成功！"<<id<<"  "<<pwd;
};



void Widget::initnavBarTreeWidget(){
    auto userItem =new QTreeWidgetItem({"用户管理"},User_Common);
    userItem->addChild(new QTreeWidgetItem({"用户账号"},User_Manage));
    userItem->addChild(new QTreeWidgetItem({"用户安全"},User_Secure));
    userItem->addChild(new QTreeWidgetItem({"用户记录"},User_Log));
    ui->navBar->addTopLevelItem(userItem);
    connect(ui->navBar,&QTreeWidget::itemClicked,[this](QTreeWidgetItem *item){
        catPage(NavType(item->type()));
    });



};
void Widget::catPage(NavType type){
    switch (type) {
    case User_Manage:
        ui->stackedWidget->setCurrentWidget(ui->page_1);
        on_usermanage();
        break;
    default:
        qDebug()<<" 该导航选项没有设计 ";
        break;

    }
};
void Widget::on_usermanage() {
    QSqlQuery query;
    if (!query.exec("SELECT * FROM custom")) {
        QMessageBox::warning(this, "管理信息查询失败", query.lastError().text());
        return;
    }

    // 如果没有用户模型则创建模型
    if (!m_user) {
        m_user = new QStandardItemModel;
        ui->usertableView->setModel(m_user);
    } else {
        // 若已有模型，清空之前的数据
        m_user->clear();
    }

    // 设置表头
    QSqlRecord record = query.record();
    int size = record.count();
    for (int i = 0; i < size; ++i) {
        m_user->setHorizontalHeaderItem(i, new QStandardItem(record.fieldName(i)));
    }

    // 填充数据
    while (query.next()) {
        QList<QStandardItem*> item_list;
        for (int i = 0; i < size; ++i) {
            item_list.append(new QStandardItem(query.value(i).toString()));
        }
        m_user->appendRow(item_list);
    }
}

