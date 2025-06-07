#include "clientdialog.h"
#include "ui_clientdialog.h"

ClientDialog::ClientDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ClientDialog)
    , webSocket(new QWebSocket)
    , isConnected(false)
{
    ui->setupUi(this);

    connect(webSocket, &QWebSocket::connected, this, &ClientDialog::onConnected);
    connect(webSocket, &QWebSocket::textMessageReceived, this, &ClientDialog::onTextMessageReceived);
    connect(webSocket, &QWebSocket::disconnected, this, &ClientDialog::on_pushButton_Disc_clicked);
    ui->pushButton_Connect->setEnabled(true);
    ui->pushButton_Send->setEnabled(false);
    ui->pushButton_Disc->setEnabled(false);
}

ClientDialog::~ClientDialog()
{
    webSocket->close();
    delete webSocket;
    delete ui;
}

void ClientDialog::on_pushButton_Connect_clicked()
{
    if (!isConnected) {
        QString url = ui->lineEdit_ServerUrl->text(); // 例如：ws://localhost:1234
        webSocket->open(QUrl(url));

        ui->pushButton_Send->setEnabled(true);
        ui->pushButton_Connect->setEnabled(false);

        ui->pushButton_Disc->setEnabled(true);
    } else {

        webSocket->close();
    }
}

void ClientDialog::onConnected()
{
    isConnected = true;
    ui->textEdit_Log->append("Connected to server.");
}

void ClientDialog::onTextMessageReceived(QString message)
{
    ui->textEdit_Log->append("Received: " + message);
}





void ClientDialog::on_pushButton_Disc_clicked()
{
    isConnected = false;
    ui->pushButton_Connect->setEnabled(true);
    ui->pushButton_Send->setEnabled(false);
    ui->pushButton_Disc->setEnabled(false);
    ui->textEdit_Log->append("Disconnected from server.");
      webSocket->close();
}



void ClientDialog::on_pushButton_Send_clicked()
{
    QString message = ui->lineEdit_Message->document()->toPlainText();
    if (isConnected && !message.isEmpty()) {
        webSocket->sendTextMessage(message);
        ui->textEdit_Log->append("Sent: " + message);
    }
}
