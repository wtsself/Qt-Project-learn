#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QDebug>
#include "logindialog.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include<QStandardItemModel>
#include<QList>
#include<QSqlRecord>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    //枚举类型
    enum NavType{
      User_Manage,
        User_Secure,
        User_Log,
        User_Common
    };
    //使用下面函数使得枚举的返回值不再是0，1，2而是枚举的名字
    Q_ENUM(NavType)
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initnavBarTreeWidget();
    void catPage(NavType type);
    void on_usermanage();




//公共槽函数
public slots:
    void work(int id,QString pwd);
private:
    Ui::Widget *ui;
    //用户模型
    QStandardItemModel * m_user;

};
#endif // WIDGET_H
