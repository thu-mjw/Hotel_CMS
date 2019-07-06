#ifndef ROOT_LOGIN_H
#define ROOT_LOGIN_H

#include <QWidget>

namespace Ui {
class root_login;
}

class root_login : public QWidget
{
    Q_OBJECT

public:
    explicit root_login(QWidget *parent = 0);
    ~root_login();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void reshow();

signals:
    void show_main();
    void show_confirm();

private:
    Ui::root_login *ui;
};

#endif // ROOT_LOGIN_H
