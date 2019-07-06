#ifndef MYORDER_H
#define MYORDER_H

#include <QWidget>

namespace Ui {
class myOrder;
}

class myOrder : public QWidget
{
    Q_OBJECT

public:
    explicit myOrder(QWidget *parent = 0);
    ~myOrder();
    QString phone;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void reshow(QString);

    void on_pushButton_3_clicked();

    void on_pay_clicked();

    void on_money_back_clicked();

    void on_in_room_clicked();

    void on_out_room_clicked();

signals:
    void show_main();
    void show_platform(QString);
    void show_score(QString,QString,QString);
    void show_pay(QString,QString,QString);
    void show_self(QString);

private:
    Ui::myOrder *ui;
};

#endif // MYORDER_H
