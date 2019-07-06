#ifndef SALEDETAIL_H
#define SALEDETAIL_H

#include <QWidget>

namespace Ui {
class saleDetail;
}

class saleDetail : public QWidget
{
    Q_OBJECT

public:
    explicit saleDetail(QWidget *parent = 0);
    ~saleDetail();
    QString hotel_name;

private slots:
    void on_pushButton_2_clicked();
    void reshow(QString);

    void on_pushButton_clicked();

    void on_toolButton_clicked();


signals:
    void show_hotel(QString);

private:
    Ui::saleDetail *ui;
};

#endif // SALEDETAIL_H
