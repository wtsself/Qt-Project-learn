#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->checkBox->setText("选啊");
    ui->checkBox->setTristate(true);
    connect(ui->checkBox,SIGNAL(stateChanged()),this,SLOT(on_pushButton_clicked()));
   btngroup=new QButtonGroup(this);
    btngroup->addButton(ui->radioButton,1);
    btngroup->addButton(ui->radioButton_2,0);
    ui->radioButton->setChecked(true);

    connect(btngroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, [=](QAbstractButton *button){
        int id = btngroup->id(button);
        qDebug() << "按钮的ID是：" << id<<"name"<<button->text();

        // 举例：根据 ID 设置 groupBox 标题
        ui->groupBox->setTitle(QString("选中按钮ID: %1").arg(id));});



}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    // 1. 打开文件选择框
    QString sourcePath = QFileDialog::getOpenFileName(
                this,
                "选择要复制的文件",
                "D:/", // 初始目录
                "所有文件 (*.*)"
                );

    if (sourcePath.isEmpty()) {

        return;
    }

    // 2. 获取文件名
    QFileInfo fileInfo(sourcePath);
    QString fileName = fileInfo.fileName();

    // 3. 构造目标路径（例如下载到 MusicPlayer/music 目录）
    QString targetPath = "D:/" + fileName;

    // 4. 检查目标文件是否已经存在
    if (QFile::exists(targetPath)) {
        QMessageBox::warning(this, "提示", "目标文件已存在！");
        return;
    }

    // 5. 复制文件
    if (QFile::copy(sourcePath, targetPath)) {
        QMessageBox::information(this, "成功", "文件复制成功！");
    } else {
        QMessageBox::critical(this, "失败", "文件复制失败！");
    }
}

void Widget::on_checkBox_stateChanged(int state)
{
    if (state == Qt::Checked) {
        qDebug() << "选中";
        int id=btngroup->checkedId();
        qDebug()<<"其他函数获取的单选的id值为："<<id;
    } else if (state == Qt::Unchecked) {
        qDebug() << "未选中";
    } else if (state == Qt::PartiallyChecked) {
        qDebug() << "部分选中";
    }
}

