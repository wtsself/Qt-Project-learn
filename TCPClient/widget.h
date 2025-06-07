#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <chat.h>
//ip地址和端口号的相关函数也被封装在Qt里
#include<QHostAddress>
//TCP网络通信已经在Qt里封装好了，只用导入就行了，注意要在项目pro文件里面添加network模块
//没有的话 先重新构建一下项目 更新依赖库
#include<QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_cancel_btn_clicked();

    void on_connect_btn_clicked();

private:
    Ui::Widget *ui;
    //QT大小写敏感，注意大小写
    QTcpSocket *socket;
};
#endif // WIDGET_H
