#ifndef ORDERCONTROLLER_H
#define ORDERCONTROLLER_H

#include <QWidget>

namespace Ui {
class orderController;
}

class orderController : public QWidget
{
    Q_OBJECT

public:
    explicit orderController(QWidget *parent = 0);
    ~orderController();
    QString hotel_name;

private slots:
    void on_pushButton_2_clicked();
    void reshow(QString);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

signals:
    void show_hotel(QString);
    void show_self(QString);

private:
    Ui::orderController *ui;
};

#endif // ORDERCONTROLLER_H
