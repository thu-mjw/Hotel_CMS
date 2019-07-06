#include "root_login.h"
#include "ui_root_login.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
root_login::root_login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::root_login)
{
    ui->setupUi(this);
    ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);
}

root_login::~root_login()
{
    delete ui;
}

void root_login::on_pushButton_clicked()
{
    QString id = ui->lineEdit_id->text();
    QString pwd = ui->lineEdit_pwd->text();
    //get pwd
    QString pwd_sql;
    QSqlQuery q;
    QString sql_select = "select * from root_user where id=:id";
    q.prepare(sql_select);
    q.bindValue(":id",id);
    q.exec();
    if(!q.next())
    {
        ui->err->setText("手机号或密码输入错误");
        return;
    }
    pwd_sql = q.value(1).toString();
    if(pwd != pwd_sql)
    {
        ui->err->setText("手机号或密码输入错误");
        return;
    }
    emit show_confirm();
    this->close();
}

void root_login::on_pushButton_2_clicked()
{
    //跳转主界面
    emit show_main();
    this->close();
}

void root_login::reshow()
{
    ui->lineEdit_id->setText("");
    ui->lineEdit_pwd->setText("");
    ui->err->setText("");
    this->show();
}
