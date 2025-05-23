#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
//弹出选择文件的框的头文件
#include <QFileDialog>
//弹出对话框
#include <QMessageBox>

#include <QKeyEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    //重写事件函数（虚函数），实现键盘点击事件
    virtual void keyPressEvent(QKeyEvent* k);
    //鼠标点击
    virtual void mousePressEvent(QMouseEvent *m);
    ~MainWindow();
private slots:
    void newActionSlot();
    void openActionSlot();
    void saveActionSlot();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
