#include "ordercontroller.h"
#include "ui_ordercontroller.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
orderController::orderController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orderController)
{
    ui->setupUi(this);
}

orderController::~orderController()
{
    delete ui;
}

void orderController::on_pushButton_2_clicked()
{
    //跳转酒店界面
    emit show_hotel(hotel_name);
    this->close();
}

void orderController::reshow(QString id)
{
    hotel_name = id;
    QSqlQuery q;
    //查询所有未完成订单数量，用来初始化QTableWidget
    QString sql_select = "select count(phone) from myorder where (status='00' or status='01' or status='02' or status='03' or status='04')";
    q.prepare(sql_select);
    q.exec();
    if(!q.next())
    {
        qDebug() << "db access err";
    }
    int num = q.value(0).toInt();
    //初始化table，设置行列及表头
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(num);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(150);
    QStringList header;
    header << "用户姓名" << "手机号" << "房间号" << "价格" << "订单状态";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    sql_select = "select user.name,user.phone,myorder.roomid,myorder.price,myorder.status from user,room,hotel,myorder where user.phone=myorder.phone and hotel.hotelname=:hotelname and hotel.hotelname=room.hotelname and hotel.hotelname=myorder.hotelname and room.roomid=myorder.roomid and (myorder.status='00' or myorder.status='01' or myorder.status='02' or myorder.status='03' or myorder.status='04')";
    q.prepare(sql_select);
    q.bindValue(":hotelname",this->hotel_name);
    q.exec();
    int index = 0;

    //逐行设置table内容
    while(q.next())
    {
        QString name = q.value(0).toString();
        QString phone = q.value(1).toString();
        QString room_id = q.value(2).toString();
        float price = q.value(3).toFloat();
        QString status = q.value(4).toString();
        ui->tableWidget->setItem(index,0,new QTableWidgetItem(name));
        ui->tableWidget->setItem(index,1,new QTableWidgetItem(phone));
        ui->tableWidget->setItem(index,2,new QTableWidgetItem(room_id));
        ui->tableWidget->setItem(index,3,new QTableWidgetItem(QString::number(price)));

     //status的数值代表订单状态
        if(status == "00")
        {
            ui->tableWidget->setItem(index,4,new QTableWidgetItem("预订待确认"));
        }
        else if(status == "01")
        {
            ui->tableWidget->setItem(index,4,new QTableWidgetItem("付款待确认"));
        }
        else if(status == "02")
        {
            ui->tableWidget->setItem(index,4,new QTableWidgetItem("退款待确认"));
        }
        else if(status == "03")
        {
            ui->tableWidget->setItem(index,4,new QTableWidgetItem("入住待确认"));
        }
        else if(status == "04")
        {
            ui->tableWidget->setItem(index,4,new QTableWidgetItem("退房待确认"));
        }
        index += 1;
    }
    this->show();
}

void orderController::on_pushButton_clicked()
{
    //获取当前行以及所需信息
    int row = ui->tableWidget->currentItem()->row();
    QString phone = ui->tableWidget->item(row,1)->text();
    QString room_id = ui->tableWidget->item(row,2)->text();
    QSqlQuery q;
    //设置订单状态为10，即已确认订单
    QString sql_insert = "update myorder set status='10' where phone=:phone and roomid=:roomid and hotelname=:hotelname";
    q.prepare(sql_insert);
    q.bindValue(":phone",phone);
    q.bindValue(":roomid",room_id);
    q.bindValue(":hotelname",this->hotel_name);
    q.exec();
    this->close();
    emit show_self(this->hotel_name);

}

void orderController::on_pushButton_3_clicked()
{
    //获取当前行以及所需信息
    int row = ui->tableWidget->currentItem()->row();
    QString phone = ui->tableWidget->item(row,1)->text();
    QString room_id = ui->tableWidget->item(row,2)->text();
    QSqlQuery q;
    //设置订单状态为11，即已确定付款
    QString sql_insert = "update myorder set status='11' where phone=:phone and roomid=:roomid and hotelname=:hotelname";
    q.prepare(sql_insert);
    q.bindValue(":phone",phone);
    q.bindValue(":roomid",room_id);
    q.bindValue(":hotelname",this->hotel_name);
    q.exec();
    this->close();
    emit show_self(this->hotel_name);
}

void orderController::on_pushButton_4_clicked()
{
    //获取当前行以及所需信息
    int row = ui->tableWidget->currentItem()->row();
    QString phone = ui->tableWidget->item(row,1)->text();
    QString room_id = ui->tableWidget->item(row,2)->text();
    QSqlQuery q;
    //设置订单状态为12，即已确认退款
    QString sql_insert = "update myorder set status='12' where phone=:phone and roomid=:roomid and hotelname=:hotelname";
    q.prepare(sql_insert);
    q.bindValue(":phone",phone);
    q.bindValue(":roomid",room_id);
    q.bindValue(":hotelname",this->hotel_name);
    q.exec();
    this->close();
    emit show_self(this->hotel_name);
}

void orderController::on_pushButton_5_clicked()
{
    //获取当前行以及所需信息
    int row = ui->tableWidget->currentItem()->row();
    QString phone = ui->tableWidget->item(row,1)->text();
    QString room_id = ui->tableWidget->item(row,2)->text();
    QSqlQuery q;
    //设置订单状态为13，即已确认入住
    QString sql_insert = "update myorder set status='13' where phone=:phone and roomid=:roomid and hotelname=:hotelname";
    q.prepare(sql_insert);
    q.bindValue(":phone",phone);
    q.bindValue(":roomid",room_id);
    q.bindValue(":hotelname",this->hotel_name);
    q.exec();
    QString sql_room = "update room set status=1,sale_num=sale_num+1 where hotelname=:hotelname and roomid=:roomid";
    q.prepare(sql_room);
    q.bindValue(":hotelname",this->hotel_name);
    q.bindValue(":roomid",room_id);
    q.exec();
    this->close();
    emit show_self(this->hotel_name);
}

void orderController::on_pushButton_6_clicked()
{
    //获取当前行以及所需信息
    int row = ui->tableWidget->currentItem()->row();
    QString phone = ui->tableWidget->item(row,1)->text();
    QString room_id = ui->tableWidget->item(row,2)->text();
    QSqlQuery q;
    //设置订单状态为14，即已确认退房
    //QString sql_del = "delete from myorder where phone=:phone and roomid=:roomid and hotelname=:hotelname";   若退款成功后删除相应订单，则使用次sql语句，注释掉下面那句，同时修改prepare();
    QString sql_insert = "update myorder set status='14' where phone=:phone and roomid=:roomid and hotelname=:hotelname";
    q.prepare(sql_insert);
    q.bindValue(":phone",phone);
    q.bindValue(":roomid",room_id);
    q.bindValue(":hotelname",this->hotel_name);
    q.exec();
    QString sql_room = "update room set status=0 where hotelname=:hotelname and roomid=:roomid";
    q.prepare(sql_room);
    q.bindValue(":hotelname",this->hotel_name);
    q.bindValue(":roomid",room_id);
    q.exec();
    this->close();
    emit show_self(this->hotel_name);
}
