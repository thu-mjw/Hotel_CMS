#ifndef HOTELSHOW_H
#define HOTELSHOW_H

#include <QWidget>

namespace Ui {
class hotelShow;
}

class hotelShow : public QWidget
{
    Q_OBJECT

public:
    explicit hotelShow(QWidget *parent = 0);
    ~hotelShow();
    QString hotel_name;

private slots:
    void reshow(QString);

    void on_pushButton_clicked();

    void on_add_room_clicked();

    void on_manage_order_clicked();

    void on_showSale_clicked();

signals:
    void show_main();
    void show_add_room(QString);
    void show_order(QString);
    void show_detail(QString);

private:
    Ui::hotelShow *ui;
};

#endif // HOTELSHOW_H
