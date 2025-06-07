#ifndef CLIENTDIALOG_H
#define CLIENTDIALOG_H

#include <QDialog>
#include <QWebSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class ClientDialog; }
QT_END_NAMESPACE

class ClientDialog : public QDialog
{
    Q_OBJECT

public:
    ClientDialog(QWidget *parent = nullptr);
    ~ClientDialog();

private slots:
    void on_pushButton_Connect_clicked();

    void onConnected();
    void onTextMessageReceived(QString message);
    void on_pushButton_Disc_clicked();


    void on_pushButton_Send_clicked();

private:
    Ui::ClientDialog *ui;
    QWebSocket *webSocket;
    bool isConnected;
};
#endif // CLIENTDIALOG_H
