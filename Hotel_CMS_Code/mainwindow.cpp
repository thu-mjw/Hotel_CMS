#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reshow()
{
    this->show();
}

//跳转至各个界面
void MainWindow::on_user_login_clicked()
{
    emit show_login();
    this->close();
}

void MainWindow::on_user_regi_clicked()
{
    emit show_regi();
    this->close();
}

void MainWindow::on_hotel_login_clicked()
{
    emit show_hotel_login();
    this->close();
}

void MainWindow::on_hotel_regi_clicked()
{
    emit show_hotel_regi();
    this->close();
}

void MainWindow::on_root_log_clicked()
{
    emit show_root_login();
    this->close();
}

void MainWindow::on_root_register_clicked()
{
    emit show_root_register();
    this->close();
}
