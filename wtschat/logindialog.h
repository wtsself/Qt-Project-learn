#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include"global.h"
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    void initHead();
    bool checkUserValid();
    bool checkPwdValid();
    void AddTipErr(TipErr te,QString tips);
    void DelTipErr(TipErr te);
    void showTip(QString str,bool b_ok);
    bool enableBtn(bool);
    void initHttpHandlers();
    QMap<TipErr, QString> _tip_errs;
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
    Ui::LoginDialog *ui;
public slots:
    void  slot_forget_pwd();
signals:
    void switchRegister();
    void switchReset();
     void sig_connect_tcp(ServerInfo);
private slots:
    void on_login_btn_clicked();
    void slot_login_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // LOGINDIALOG_H
