#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots:
    void on_login_2_clicked();

    void on_reg_clicked();

    void on_main_clicked();
    void reshow();

signals:
    void show_regi();
    void show_platform(QString);
    void show_main();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
