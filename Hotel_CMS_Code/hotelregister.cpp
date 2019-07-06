#include "hotelregister.h"
#include "ui_hotelregister.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
hotelRegister::hotelRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::hotelRegister)
{
    ui->setupUi(this);
    ui->pwd_edit->setEchoMode(QLineEdit::Password);
    ui->pwd_edit_2->setEchoMode(QLineEdit::Password);
}

hotelRegister::~hotelRegister()
{
    delete ui;
}

void hotelRegister::on_reg_clicked()
{
    int flag = 0;
    QString hotelname = ui->name_edit->text();
    QString city = ui->city_edit->text();
    QString location = ui->location_edit->text();
    QString phone = ui->phone_edit->text();
    QString pwd = ui->pwd_edit->text();
    QString pwd2 = ui->pwd_edit_2->text();
    //判断非空
    if(hotelname.isEmpty())
    {
        flag = 1;
        ui->err_name->setText("名字不能为空!");
    }
    if(city.isEmpty())
    {
        flag = 1;
        ui->err_city->setText("城市不能为空!");
    }
    if(location.isEmpty())
    {
        flag = 1;
        ui->err_loca->setText("区域不能为空!");
    }
    if(phone.isEmpty())
    {
        flag = 1;
        ui->err_phone->setText("手机号不能为空!");
    }
    //判断密码一致
    if(pwd != pwd2)
    {
        ui->err_pwd->setText("密码前后不一致!");
        return;
    }

    //手机号格式为1开头的11位数字
    QRegExp rx("1[0-9]{10}");
    if(!rx.exactMatch(phone))
    {
        flag = 1;
        ui->err_phone->setText("手机号码格式错误");
    }
    if(flag)
    {
        return ;
    }
    //跳转
    QSqlQuery q;
    //写入数据库hotel_regi
    QString sql_insert = "insert into hotel_regi values(?,?,?,?,?)";
    q.prepare(sql_insert);
    q.addBindValue(hotelname);
    q.addBindValue(city);
    q.addBindValue(location);
    q.addBindValue(phone);
    q.addBindValue(pwd);
    q.exec();
    emit show_main();
    this->close();
}

void hotelRegister::reshow()
{
    //刷新
    ui->err_city->setText("");
    ui->err_loca->setText("");
    ui->err_name->setText("");
    ui->err_phone->setText("");
    ui->err_pwd->setText("");
    ui->city_edit->setText("");
    ui->location_edit->setText("");
    ui->phone_edit->setText("");
    ui->name_edit->setText("");
    ui->pwd_edit->setText("");
    ui->pwd_edit_2->setText("");
    this->show();
}

void hotelRegister::on_reg_2_clicked()
{
    //跳转主界面
    emit show_main();
    this->close();
}
