#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void show_login();
    void show_regi();
    void show_hotel_login();
    void show_hotel_regi();
    void show_root_login();
    void show_root_register();

private slots:
    void reshow();

    void on_user_login_clicked();

    void on_user_regi_clicked();

    void on_hotel_login_clicked();

    void on_hotel_regi_clicked();

    void on_root_log_clicked();

    void on_root_register_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
