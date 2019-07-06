#ifndef SHOWPAY_H
#define SHOWPAY_H

#include <QWidget>

namespace Ui {
class showPay;
}

class showPay : public QWidget
{
    Q_OBJECT

public:
    explicit showPay(QWidget *parent = 0);
    ~showPay();
    QString phone;
    QString name;
    QString roomid;

private slots:
    void on_pushButton_clicked();
    void reshow(QString,QString,QString);

signals:
    void show_order(QString phone);

private:
    Ui::showPay *ui;
};

#endif // SHOWPAY_H
