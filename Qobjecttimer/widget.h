#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include<QString>
#define TIMEOUT 1*1000

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
   explicit Widget(QWidget *parent = nullptr);
    //时间到了后调用定时器事件
    //这里的定时器事件处理函数为虚函数是因为Q类的定时器有多种，所以用到多态的方法来指向不同的子类定时器
    virtual void timerEvent(QTimerEvent *event);

    ~Widget();

private slots:
    void on_startbutton_clicked();

    void on_stopbutton_clicked();

private:
    Ui::Widget *ui;
    //定时器id
    int myTimerId;
    //图片id
    int picId;
};
#endif // WIDGET_H
