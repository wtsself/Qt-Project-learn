#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("登陆");
    connect(this,&LoginDialog::jump_to_main_signal,this,&LoginDialog::emit_jump_page_to_main);
    initsql();

}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::initsql(){
    //连接数据库
    db=QSqlDatabase::addDatabase("QMYSQL"); //加载数据库驱动

    //初始化数据库
    db.setDatabaseName("test");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("123456");
    if(db.open()){
        qDebug()<<"数据库连接提示:连接成功";

    }
    else{
        qDebug()<<"数据库连接提示:连接失败";
    }

}

void  LoginDialog::emit_jump_page_to_main(int id ,QString pwd){

emit commit_info_signal(id,pwd);
 this->hide();

};

void LoginDialog::on_loginBtn_clicked()
{
int ac=ui->account->text().toInt();
auto pwd=ui->pwd->text();

qDebug()<<"用户账户"<<" :"<<ac;
qDebug()<<"用户密码"<<" :"<<pwd;


QSqlQuery query;
//下面的两个操作是用prepare函数占位对应的值
query.prepare("SELECT *FROM custom where id=? and password=?");
query.bindValue(0,ac);
query.bindValue(1,pwd);
if(!query.exec()){
    QMessageBox::warning(this,"登陆",query.lastError().text());
    return;
}
if(query.size()>0){
    //跳转页面，发出信号（我要跳转了！），接受信号后，转交槽函数继续发出页面转换信号（你跳转吧！），携带必要的数据
    emit jump_to_main_signal(ac,pwd);
   // done(QDialog::Accepted);
}
else{
    qWarning()<<"登陆错误";
}



}
