#include "widget.h"
#include "logindialog.h"
#include <QApplication>

//这里用main文件来管理页面跳转
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     //创建对象，接受信号
    LoginDialog login;
    Widget w;

    // 连接信号和槽
    QObject::connect(&login, &LoginDialog::commit_info_signal,
                     &w, &Widget::work);

    login.show();

    return a.exec(); // 用 a.exec()，而不是 login.exec()
}
