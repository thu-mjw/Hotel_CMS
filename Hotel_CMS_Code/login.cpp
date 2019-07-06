#include "login.h"
#include "ui_login.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    //密码输入时不显示数字
    ui->pwd_edit->setEchoMode(QLineEdit::Password);
}

login::~login()
{
    delete ui;
}

void login::on_login_2_clicked()
{
    QString phone = ui->phone_edit->text();
    QString pwd = ui->pwd_edit->text();
    //get pwd
    QString pwd_sql;
    QSqlQuery q;
    QString sql_select = "select * from user where phone=:phone";
    q.prepare(sql_select);
    q.bindValue(":phone",phone);
    q.exec();
    //判断手机号是否已注册过
    if(!q.next())
    {
        ui->login_err->setText("手机号或密码输入错误");
        return;
    }
    pwd_sql = q.value(1).toString();
    //判断密码正误
    if(pwd != pwd_sql)
    {
        ui->login_err->setText("手机号或密码输入错误");
        return;
    }
        //跳转订房平台
    emit show_platform(phone);
    this->close();
}

void login::on_reg_clicked()
{
    //跳转regi
    emit show_regi();
    this->close();
}

void login::on_main_clicked()
{
       //跳转主界面
    emit show_main();
    this->close();
}

void login::reshow()
{
        //界面刷新
    ui->phone_edit->setText("");
    ui->pwd_edit->setText("");
    ui->login_err->setText("");
    this->show();
}
