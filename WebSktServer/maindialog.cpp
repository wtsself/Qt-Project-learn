#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDebug>

MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    websktserver = new QWebSocketServer("server", QWebSocketServer::NonSecureMode, this);

    ui->pushButton_Sen->setEnabled(false);
    ui->pushButton_Disc->setEnabled(false);

    connect(websktserver, SIGNAL(newConnection()), this, SLOT(OnNewConnect()));
    connect(ui->pushButton_Con, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_Con_clicked()));
    connect(ui->pushButton_Disc, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_Disc_clicked()));
    connect(ui->pushButton_Sen, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_Sen_clicked()));
}

MainDialog::~MainDialog()
{
    for (QWebSocket *client : sktclients) {
        client->close();
        client->deleteLater();
    }
    websktserver->close();
    delete ui;
}

void MainDialog::OnNewConnect()
{
    psocket = websktserver->nextPendingConnection();
    connect(psocket, SIGNAL(textMessageReceived(QString)), this, SLOT(ProTextMsg(QString)));
    connect(psocket, SIGNAL(disconnected()), this, SLOT(OnDisConnect()));

    QString stritem = psocket->peerAddress().toString();
    ui->listWidget_Cli->addItem(stritem);
    sktclients << psocket;

    qDebug() << "New client connected:" << stritem;
}

void MainDialog::OnDisConnect()
{
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (client) {
        QString clientIp = client->peerAddress().toString();
        sktclients.removeAll(client);

        // 从客户端列表 UI 中移除该 IP
        for (int i = 0; i < ui->listWidget_Cli->count(); ++i) {
            if (ui->listWidget_Cli->item(i)->text() == clientIp) {
                delete ui->listWidget_Cli->takeItem(i);
                break;
            }
        }

        client->deleteLater();
        qDebug() << "Client disconnected:" << clientIp;
    }
}

void MainDialog::ProTextMsg(QString msg)
{
    QString from = psocket->peerAddress().toString();
    QString log = QString("[%1] %2").arg(from).arg(msg);
    ui->textEdit_Rec->append(log);

    qDebug() << "Received from client:" << log;
}

void MainDialog::on_pushButton_Con_clicked()
{
    int iport = ui->spinBox->text().toUInt();

    if (websktserver->listen(QHostAddress::Any, iport)) {
        qDebug() << "Server listening on port" << iport;
        ui->pushButton_Con->setEnabled(false);
        ui->pushButton_Disc->setEnabled(true);
        ui->pushButton_Sen->setEnabled(true);
    } else {
        qDebug() << "Failed to listen on port" << iport;
    }
}

void MainDialog::on_pushButton_Disc_clicked()
{
    for (QWebSocket *client : sktclients) {
        client->close();
        client->deleteLater();
    }
    sktclients.clear();
    ui->listWidget_Cli->clear();

    websktserver->close();
    ui->pushButton_Con->setEnabled(true);
    ui->pushButton_Disc->setEnabled(false);
    ui->pushButton_Sen->setEnabled(false);

    qDebug() << "Server stopped.";
}

void MainDialog::on_pushButton_Sen_clicked()
{
    QString strmsg = ui->textEdit_Sen->document()->toPlainText();
    for (int i = 0; i < sktclients.size(); ++i) {
        sktclients.at(i)->sendTextMessage(strmsg);
    }


    qDebug() << "Message sent to all clients:" << strmsg;
}
