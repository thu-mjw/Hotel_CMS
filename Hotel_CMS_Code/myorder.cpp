#include "myorder.h"
#include "ui_myorder.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
myOrder::myOrder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myOrder)
{
    ui->setupUi(this);
}

myOrder::~myOrder()
{
    delete ui;
}

void myOrder::on_pushButton_clicked()
{
    emit show_platform(this->phone);
    this->close();
}

void myOrder::on_pushButton_2_clicked()
{
    //跳转主界面
    emit show_main();
    this->close();
}

void myOrder::reshow(QString phone)
{
    this->phone = phone;
    QSqlQuery q;
    //设置酒店名称
    QString sql_select = "select name from user where phone=:phone";
    q.prepare(sql_select);
    q.bindValue(":phone",this->phone);
    q.exec();
    if(!q.next())
    {
        qDebug() << "db access err";
    }
    QString user_name = q.value(0).toString();
    ui->user_name->setText(user_name);
    //查找订单数量，初始化QTableWidget
    sql_select = "select count(status) from myorder where phone=:phone";
    q.prepare(sql_select);
    q.bindValue(":phone",this->phone);
    q.exec();
    if(!q.next())
    {
        qDebug() << "db access err";
    }
    int num = q.value(0).toInt();
    //设置行数，列数以及表头
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(num);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(150);
    QStringList header;
    header << "酒店名" << "地区" << "房间号" << "房间类型" << "价格" << "入住时间" << "退房时间" << "订单状态";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //查找对应订单信息
    sql_select = "select myorder.hotelname,location,myorder.roomid,type,myorder.price,myorder.status,myorder.intime,myorder.outtime from myorder,hotel,room where phone=:phone and myorder.hotelname=room.hotelname and hotel.hotelname=room.hotelname and room.roomid=myorder.roomid";
    q.prepare(sql_select);
    q.bindValue(":phone",this->phone);
    q.exec();
    int index = 0;
    //逐行设置订单
    while(q.next())
    {
        QString name = q.value(0).toString();
        QString location = q.value(1).toString();
        QString room_id = q.value(2).toString();
        QString room_type = q.value(3).toString();
        float price = q.value(4).toFloat();
        QString status = q.value(5).toString();
        QString in_time = q.value(6).toString();
        QString out_time = q.value(7).toString();
        ui->tableWidget->setItem(index,0,new QTableWidgetItem(name));
        ui->tableWidget->setItem(index,1,new QTableWidgetItem(location));
        ui->tableWidget->setItem(index,2,new QTableWidgetItem(room_id));
        ui->tableWidget->setItem(index,3,new QTableWidgetItem(room_type));
        ui->tableWidget->setItem(index,4,new QTableWidgetItem(QString::number(price)));
        ui->tableWidget->setItem(index,5,new QTableWidgetItem(in_time));
        ui->tableWidget->setItem(index,6,new QTableWidgetItem(out_time));
        if(status == "00")
        {
            ui->tableWidget->setItem(index,7,new QTableWidgetItem("预订待确认"));
        }
        else if(status == "10")
        {
            ui->tableWidget->setItem(index,7,new QTableWidgetItem("预订已确认"));
        }
        else if(status == "01")
        {
            ui->tableWidget->setItem(index,7,new QTableWidgetItem("付款待确认"));
        }
        else if(status == "11")
        {
            ui->tableWidget->setItem(index,7,new QTableWidgetItem("付款已确认"));
        }
        else if(status == "02")
        {
            ui->tableWidget->setItem(index,7,new QTableWidgetItem("退款待确认"));
        }
        else if(status == "12")
        {
            ui->tableWidget->setItem(index,7,new QTableWidgetItem("退款已确认"));
        }
        else if(status == "03")
        {
            ui->tableWidget->setItem(index,7,new QTableWidgetItem("入住待确认"));
        }
        else if(status == "13")
        {
            ui->tableWidget->setItem(index,7,new QTableWidgetItem("入住已确认"));
        }
        else if(status == "04")
        {
            ui->tableWidget->setItem(index,7,new QTableWidgetItem("退房待确认"));
        }
        else if(status == "14")
        {
            ui->tableWidget->setItem(index,7,new QTableWidgetItem("退房已确认"));
        }
        index += 1;
    }
    this->show();
}
//评分按键触发
void myOrder::on_pushButton_3_clicked()
{
    //查找当前选中行以及对应内容
    int row = ui->tableWidget->currentItem()->row();
    QString hotelname = ui->tableWidget->item(row,0)->text();
    QString room_id = ui->tableWidget->item(row,2)->text();
    emit show_score(this->phone,hotelname,room_id);
    this->close();
}
//付款按键触发
void myOrder::on_pay_clicked()
{
    int row = ui->tableWidget->currentItem()->row();
    QString hotelname = ui->tableWidget->item(row,0)->text();
    QString room_id = ui->tableWidget->item(row,2)->text();
    emit show_pay(this->phone,hotelname,room_id);
    this->close();
}
//退款按键触发
void myOrder::on_money_back_clicked()
{
    int row = ui->tableWidget->currentItem()->row();
    QString hotelname = ui->tableWidget->item(row,0)->text();
    QString room_id = ui->tableWidget->item(row,2)->text();
    QSqlQuery q;
    QString sql_select = "update myorder set status='02' where phone=:phone and hotelname=:hotelname and roomid=:roomid";
    q.prepare(sql_select);
    q.bindValue(":phone",this->phone);
    q.bindValue(":hotelname",hotelname);
    q.bindValue(":roomid",room_id);
    q.exec();
    this->close();
    emit show_self(this->phone);
}

void myOrder::on_in_room_clicked()
{
    int row = ui->tableWidget->currentItem()->row();
    QString hotelname = ui->tableWidget->item(row,0)->text();
    QString room_id = ui->tableWidget->item(row,2)->text();
    QSqlQuery q;
    QString sql_select = "update myorder set status='03' where phone=:phone and hotelname=:hotelname and roomid=:roomid";
    q.prepare(sql_select);
    q.bindValue(":phone",this->phone);
    q.bindValue(":hotelname",hotelname);
    q.bindValue(":roomid",room_id);
    q.exec();
    this->close();
    emit show_self(this->phone);
}

void myOrder::on_out_room_clicked()
{
    int row = ui->tableWidget->currentItem()->row();
    QString hotelname = ui->tableWidget->item(row,0)->text();
    QString room_id = ui->tableWidget->item(row,2)->text();
    QSqlQuery q;
    QString sql_select = "update myorder set status='04' where phone=:phone and hotelname=:hotelname and roomid=:roomid";
    q.prepare(sql_select);
    q.bindValue(":phone",this->phone);
    q.bindValue(":hotelname",hotelname);
    q.bindValue(":roomid",room_id);
    q.exec();
    this->close();
    emit show_self(this->phone);
}
