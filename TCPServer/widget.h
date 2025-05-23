#ifndef WIDGET_H
#define WIDGET_H
//定义服务器的端口
#define PORT 8000
#include <QWidget>
//服务器专属类
#include <QTcpServer>

#include <QTcpSocket>
#include <mythread.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE



class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public slots:
    void newClientHandler();
    //注意，定义了槽函数就要用，否则会报错，要么就都注释了
    //void newClientInfo();

    //由于信号带有参数，所以这里的槽函数也要携带参数来接收
    void threadSlot(QByteArray b);

private:
    Ui::Widget *ui;
    //客户端没有对象，服务器有对象
    QTcpServer *server;
};
#endif // WIDGET_H
