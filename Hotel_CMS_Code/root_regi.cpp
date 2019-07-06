#include "root_regi.h"
#include "ui_root_regi.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
root_regi::root_regi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::root_regi)
{
    ui->setupUi(this);
    ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);
    ui->lineEdit_pwd_2->setEchoMode(QLineEdit::Password);
}

root_regi::~root_regi()
{
    delete ui;
}

void root_regi::on_pushButton_clicked()
{
    int flag = 0;
    QString name = ui->lineEdit_user->text();
    if(name.isEmpty())
    {
        flag = 1;
        ui->err_user->setText("用户名不能为空!");
    }
    QString pwd = ui->lineEdit_pwd->text();
    QString pwd2 = ui->lineEdit_pwd_2->text();
    //get phone_sql
    QSqlQuery q;
    QString sql_select = "select * from root_user where id=:id";
    q.prepare(sql_select);
    q.bindValue(":id",name);
    q.exec();
    if(q.next())
    {
        ui->err_user->setText("该用户名已被注册!");
        return;
    }
    if(pwd != pwd2)
    {
        ui->err->setText("密码前后不一致!");
        return;
    }
    //跳转
    if(flag == 1)
    {
        return ;
    }
    QString sql_insert = "insert into root_user values(?,?)";
    q.prepare(sql_insert);
    q.addBindValue(name);
    q.addBindValue(pwd);
    q.exec();
    emit show_confirm();
    this->close();
}


void root_regi::on_pushButton_2_clicked()
{
    //跳转主界面
    emit show_main();
    this->close();
}

void root_regi::reshow()
{
    ui->err_user->setText("");
    ui->lineEdit_pwd->setText("");
    ui->lineEdit_pwd_2->setText("");
    ui->lineEdit_user->setText("");
    ui->err->setText("");
    this->show();
}
