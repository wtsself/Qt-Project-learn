#include "widget.h"
#include "ui_widget.h"
#include <QString>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
//设置窗口大小，标题，字体
//    this->setMaximumSize(200,300);
//    this->setMinimumSize(200,300);
    this->setWindowTitle("计算器");
    QFont f("仿宋",12);
    ui->input->setFont(f);
    //按钮上放图片
    //QIcon con(”地址，层级用\\表示"):
    //ui->btn_D->setIcon(con);

    //改变按钮的颜色
    ui->btn_e->setStyleSheet("background:red");

}

Widget::~Widget()
{
    delete ui;
}


//为显示的字符设置expression字符串来显示
void Widget::on_btn_0_clicked()
{
    expression += "0";
    ui->input->setText(expression);
}

void Widget::on_btn_1_clicked()
{
    expression += "1";
    ui->input->setText(expression);
}
void Widget::on_btn_2_clicked()
{
    expression += "2";
    ui->input->setText(expression);
}
void Widget::on_btn_3_clicked()
{
    expression += "3";
    ui->input->setText(expression);
}
void Widget::on_btn_4_clicked()
{
    expression += "4";
    ui->input->setText(expression);
}
void Widget::on_btn_5_clicked()
{
    expression += "5";
    ui->input->setText(expression);
}
void Widget::on_btn_6_clicked()
{
    expression += "6";
    ui->input->setText(expression);
}
void Widget::on_btn_7_clicked()
{
    expression += "7";
    ui->input->setText(expression);
}
void Widget::on_btn_8_clicked()
{
    expression += "8";
    ui->input->setText(expression);
}
void Widget::on_btn_9_clicked()
{
    expression += "9";
    ui->input->setText(expression);
}
void Widget::on_btn_a_clicked()
{
    expression += "+";
    ui->input->setText(expression);
}
void Widget::on_btn_d_clicked()
{
    expression += "-";
    ui->input->setText(expression);
}
void Widget::on_btn_p_clicked()
{
    expression += "*";
    ui->input->setText(expression);
}
void Widget::on_btn_m_clicked()
{
    expression += "/";
    ui->input->setText(expression);
}
void Widget::on_btn_lk_clicked()
{
    expression += "(";
    ui->input->setText(expression);
}

void Widget::on_btn_rk_clicked()
{
    expression += ")";
    ui->input->setText(expression);
}



void Widget::on_btn_da_clicked()
{
    expression.clear();
    ui->input->clear();
}

void Widget::on_btn__clicked()
{
    //QString的函数，用以减去末尾n位
    expression.chop(1);
    ui->input->setText(expression);

}

//这里是用来处理字符串的计算
void Widget::on_btn_e_clicked()
{
    // 1. 检查表达式是否为空
    if (expression.isEmpty()) {
        ui->input->setText("错误：空表达式");
        return;
    }

    // 2. 使用 QJSEngine 计算表达式
    QJSEngine calculator;
    QJSValue result = calculator.evaluate(expression);

    // 3. 检查结果是否有效
    if (result.isError()) {
        ui->input->setText("错误：无效表达式");
        expression.clear();
    } else {
        // 4. 显示结果，并更新 expression 为结果值（便于继续计算）
        double finalValue = result.toNumber();
        expression = QString::number(finalValue, 'g', 10);  // 去除非必要小数位
        ui->input->setText(expression);
    }
}
