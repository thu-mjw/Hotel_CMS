#include "hotellogin.h"
#include "ui_hotellogin.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
hotelLogin::hotelLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::hotelLogin)
{
    ui->setupUi(this);
    ui->pwd_edit->setEchoMode(QLineEdit::Password);
}

hotelLogin::~hotelLogin()
{
    delete ui;
}
//登录按键触发
void hotelLogin::on_login_clicked()
{
    QString phone = ui->phone_edit->text();
    QString pwd = ui->pwd_edit->text();
    QSqlQuery q;
    QString sql_select = "select * from hotel where manager=:phone";
    q.prepare(sql_select);
    q.bindValue(":phone",phone);
    q.exec();
    if(!q.next())
    {
        ui->err_pwd->setText("用户不存在或密码错误");
        return;
    }
    //查找密码
    QString pwd_sql = q.value(4).toString();
    QString hotel_name = q.value(0).toString();
    if(pwd != pwd_sql)
    {
        ui->err_pwd->setText("用户不存在或密码错误");
        return;
    }
    //密码正确，跳转
    emit show_hotel(hotel_name);
    this->close();
}

void hotelLogin::reshow()
{
    //刷新
    ui->err_pwd->setText("");
    ui->phone_edit->setText("");
    ui->pwd_edit->setText("");
    this->show();
}

void hotelLogin::on_pushButton_clicked()
{
    //跳转主界面
    emit show_main();
    this->close();
}
