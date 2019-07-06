#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>

namespace Ui {
class regi;
}

class regi : public QWidget
{
    Q_OBJECT

public:
    explicit regi(QWidget *parent = 0);
    ~regi();

private slots:
    void on_reg_clicked();
    void reshow();
    void on_login_clicked();
    void on_main_clicked();

signals:
    void show_platform(QString);
    void show_login();
    void show_main();

private:
    Ui::regi *ui;
};

#endif // REGISTER_H
