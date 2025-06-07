#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
      ui->pass_lineEdit->setEchoMode(QLineEdit::Password);
      connect(ui->reg_btn,&QPushButton::clicked,this,&LoginDialog::switchRegister);
  }

  LoginDialog::~LoginDialog()
  {
      delete ui;
  }
