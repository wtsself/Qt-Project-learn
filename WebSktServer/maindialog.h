#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

#include <QWebSocketServer>
#include <QWebSocket>
#include<QHostAddress>

QT_BEGIN_NAMESPACE
namespace Ui { class MainDialog; }
QT_END_NAMESPACE

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    MainDialog(QWidget *parent = nullptr);
    ~MainDialog();

private:
    Ui::MainDialog *ui;

    //服务器对象
    QWebSocketServer *websktserver;
    //存储客户的容器
    QList<QWebSocket*> sktclients;
    //客户对象
    QWebSocket * psocket;
    //日期时间对象
    QDateTime *currentdatatime;
private slots:
    void OnNewConnect();

    void ProTextMsg(QString msg);
    void OnDisConnect();
    void on_pushButton_Con_clicked();
    void on_pushButton_Disc_clicked();
    void on_pushButton_Sen_clicked();
};
#endif // MAINDIALOG_H
