#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QJSEngine>

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
    void on_btn_0_clicked();
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_9_clicked();
    void on_btn_a_clicked();
    void on_btn_d_clicked();
    void on_btn_p_clicked();
    void on_btn_m_clicked();
    void on_btn_lk_clicked();
    void on_btn_rk_clicked();
    void on_btn_da_clicked();
    void on_btn__clicked();
    void on_btn_e_clicked();

private:
    Ui::Widget *ui;
    QString expression;
};
#endif // WIDGET_H
