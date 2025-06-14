#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include "registerdialog.h"

namespace Ui {
class MainWindow;
}

enum UIStatus{
    LOGIN_UI,
    REGISTER_UI,
    RESET_UI,
    CHAT_UI
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void SlotSwitchReg();






private:
    void offlineLogin();
    Ui::MainWindow *ui;
    LoginDialog* _login_dlg;
    RegisterDialog* _reg_dlg;

    UIStatus _ui_status;
};

#endif // MAINWINDOW_H
