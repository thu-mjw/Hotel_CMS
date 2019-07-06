#include "hotelshow.h"
#include "ui_hotelshow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
hotelShow::hotelShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::hotelShow)
{
    ui->setupUi(this);
}

hotelShow::~hotelShow()
{
    delete ui;
}

void hotelShow::reshow(QString name)
{
    this->hotel_name = name;
    ui->hotel_name->setText(name);
    QSqlQuery q;
    QString sql_select = "select * from hotel where hotelname=:hotelname";
    q.prepare(sql_select);
    q.bindValue(":hotelname",name);
    q.exec();
    if(!q.next())
    {
        qDebug() << "err";
    }

    //统计空闲房间数并输出
    sql_select = "select count(roomid) from room where hotelname=:hotelname and status=0";
    q.prepare(sql_select);
    q.bindValue(":hotelname",hotel_name);
    q.exec();
    if(!q.next())
    {
        qDebug() << "err";
    }
    int num = q.value(0).toInt();
    ui->free_num->setText(QString::number(num));
    this->show();
}

void hotelShow::on_pushButton_clicked()
{
    //跳转主界面
    emit show_main();
    this->close();
}

void hotelShow::on_add_room_clicked()
{
    //跳转添加客房
    emit show_add_room(hotel_name);
    this->close();
}

void hotelShow::on_manage_order_clicked()
{
    //跳转订单管理
    emit show_order(hotel_name);
    this->close();
}

void hotelShow::on_showSale_clicked()
{
    //跳转销售情况
    emit show_detail(hotel_name);
    this->close();
}
