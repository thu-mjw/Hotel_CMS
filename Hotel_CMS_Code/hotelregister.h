#ifndef HOTELREGISTER_H
#define HOTELREGISTER_H

#include <QWidget>

namespace Ui {
class hotelRegister;
}

class hotelRegister : public QWidget
{
    Q_OBJECT

public:
    explicit hotelRegister(QWidget *parent = 0);
    ~hotelRegister();

private slots:
    void on_reg_clicked();
    void reshow();

    void on_reg_2_clicked();

signals:
    void show_hotel(QString);
    void show_main();

private:
    Ui::hotelRegister *ui;
};

#endif // HOTELREGISTER_H
