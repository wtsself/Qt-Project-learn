#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QFileSystemModel>
#include <QStandardItemModel>
#include<QMessageBox>
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
    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::Widget *ui;
    QFileSystemModel *fsmodel;//定义文件数据模型变量
};
#endif // WIDGET_H
