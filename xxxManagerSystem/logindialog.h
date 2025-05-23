#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlDatabase>
#include<QSqlError>
#include<QMessageBox>
#include<QDebug>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    void initsql();

signals:
    //信号没有返回值，可以有参数,信号函数不需要定义，只需要声明
    void jump_to_main_signal(int id,QString pwd);
    void commit_info_signal(int id,QString pwd);


private slots:
    void on_loginBtn_clicked();
    void emit_jump_page_to_main(int id ,QString pwd);

private:
    Ui::LoginDialog *ui;
       QSqlDatabase db;
};

#endif // LOGINDIALOG_H
