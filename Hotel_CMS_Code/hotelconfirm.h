#ifndef HOTELCONFIRM_H
#define HOTELCONFIRM_H

#include <QWidget>

namespace Ui {
class hotelConfirm;
}

class hotelConfirm : public QWidget
{
    Q_OBJECT

public:
    explicit hotelConfirm(QWidget *parent = 0);
    ~hotelConfirm();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void reshow();

signals:
    void show_main();
    void show_self();

private:
    Ui::hotelConfirm *ui;
};

#endif // HOTELCONFIRM_H
