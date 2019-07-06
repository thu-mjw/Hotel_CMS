#ifndef HOTELLOGIN_H
#define HOTELLOGIN_H

#include <QWidget>

namespace Ui {
class hotelLogin;
}

class hotelLogin : public QWidget
{
    Q_OBJECT

public:
    explicit hotelLogin(QWidget *parent = 0);
    ~hotelLogin();

private slots:
    void on_login_clicked();
    void reshow();

    void on_pushButton_clicked();

signals:
    void show_hotel(QString);
    void show_main();

private:
    Ui::hotelLogin *ui;
};

#endif // HOTELLOGIN_H
