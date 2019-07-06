 #include "regi.h"
#include "ui_regi.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
regi::regi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regi)
{
    ui->setupUi(this);
    //密码输入时不显示数字
    ui->pwd_edit->setEchoMode(QLineEdit::Password);
    ui->pwd_edit2->setEchoMode(QLineEdit::Password);
}

regi::~regi()
{
delete ui;
}

void regi::on_reg_clicked()
{
    //判断非空
    int flag = 0;
    QString name = ui->name_edit->text();
    if(name.isEmpty())
    {
        flag = 1;
        ui->err_name->setText("姓名不能为空!");
    }
    QString phone = ui->phone_edit->text();
    if(phone.isEmpty())
    {
        flag = 1;
        ui->err_phone->setText("手机号不能为空!");
    }
    //正则判断phone
    //首位为1，共计11位
    QRegExp rx("1[0-9]{10}");
    if(!rx.exactMatch(phone))
    {
        flag = 1;
        ui->err_phone->setText("手机号码格式错误!");
    }
    QString pwd = ui->pwd_edit->text();
    QString pwd2 = ui->pwd_edit2->text();
    //get phone_sql
    QSqlQuery q;
    QString sql_select = "select * from user where phone=:phone";
    q.prepare(sql_select);
    q.bindValue(":phone",phone);
    q.exec();
    if(q.next())
    {
        ui->err_phone->setText("该手机号已被注册!");
        return;
    }
    if(pwd != pwd2)
    {
        ui->err_pwd->setText("密码前后不一致!");
        return;
    }
    //跳转
    if(flag == 1)
    {
        return ;
    }
    //写入数据库
    QString sql_insert = "insert into user values(?,?,?)";
    q.prepare(sql_insert);
    q.addBindValue(phone);
    q.addBindValue(pwd);
    q.addBindValue(name);
    q.exec();
    //跳转订房平台
    emit show_platform(phone);
    this->close();
}
    //界面刷新
void regi::reshow()
{
    ui->err_name->setText("");
    ui->name_edit->setText("");
    ui->phone_edit->setText("");
    ui->pwd_edit->setText("");
    ui->pwd_edit2->setText("");
    ui->err_phone->setText("");
    ui->err_pwd->setText("");
    this->show();
}
    //跳转登录
void regi::on_login_clicked()
{
    emit show_login();
    this->close();
}
   //跳转主界面
void regi::on_main_clicked()
{
    emit show_main();
    this->close();
}
