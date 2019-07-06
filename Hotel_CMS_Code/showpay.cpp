#include "showpay.h"
#include "ui_showpay.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
showPay::showPay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showPay)
{
    ui->setupUi(this);
}

showPay::~showPay()
{
    delete ui;
}

void showPay::on_pushButton_clicked()
{
    QSqlQuery q;
    QString sql_select = "update myorder set status='01' where phone=:phone and hotelname=:hotelname and roomid=:roomid";
    q.prepare(sql_select);
    q.bindValue(":phone",this->phone);
    q.bindValue(":hotelname",this->name);
    q.bindValue(":roomid",this->roomid);
    q.exec();
    emit show_order(this->phone);
    this->close();
}

void showPay::reshow(QString phone, QString name, QString roomid)
{
    this->phone = phone;
    this->name = name;
    this->roomid = roomid;
    this->show();
}
