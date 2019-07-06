#include "showroom.h"
#include "ui_showroom.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QImage>
showRoom::showRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showRoom)
{
    ui->setupUi(this);
}

showRoom::~showRoom()
{
    delete ui;
}

void showRoom::on_pushButton_2_clicked()
{
    emit show_platform(this->phone);
    this->close();
}

void showRoom::on_pushButton_clicked()
{
    QString in_time = ui->lineEdit_in_time->text();
    QString out_time = ui->lineEdit_out_time->text();
    QSqlQuery q;
    QString sql_insert = "insert into myorder values(?,?,?,?,?,?,?)";
    q.prepare(sql_insert);
    q.addBindValue(this->phone);
    q.addBindValue(this->name);
    q.addBindValue(this->roomid);
    q.addBindValue("00");
    q.addBindValue(this->price);
    q.addBindValue(in_time);
    q.addBindValue(out_time);
    q.exec();
    emit show_order(this->phone);
    this->close();
}

void showRoom::reshow(QString phone, QString name, QString roomid,float price)
{
    this->price = price;
    this->phone = phone;
    this->name = name;
    this->roomid = roomid;
    ui->hotelname->setText(name);
    ui->roomid->setText(roomid);
    QSqlQuery q;
    QString sql = "select describe,picture from room where hotelname=:hotelname and roomid=:roomid";
    q.prepare(sql);
    q.bindValue(":hotelname",name);
    q.bindValue(":roomid",roomid);
    q.exec();
    if(!q.next())
    {
        qDebug() << "db access err";
    }
    QString describe = q.value(0).toString();
    QString pic_url = q.value(1).toString();
    QImage image,result;
    image.load(pic_url);
    result = image.scaled(ui->room_pic->width(),ui->room_pic->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->room_pic->setPixmap(QPixmap::fromImage(result));
    ui->room_describe->setText(describe);
    ui->lineEdit_in_time->setText("");
    ui->lineEdit_out_time->setText("");
    this->show();
}
