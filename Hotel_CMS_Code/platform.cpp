#include "platform.h"
#include "ui_platform.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
platform::platform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::platform)
{
    ui->setupUi(this);
}

platform::~platform()
{
    delete ui;
}

void platform::reshow(QString phone)
{
    this->phone = phone;
    QSqlQuery q;
    //设置用户名称
    QString sql_select = "select name from user where phone=:phone";
    q.prepare(sql_select);
    q.bindValue(":phone",phone);
    q.exec();
    if(!q.next())
    {
        qDebug() << "err";
    }
    QString name = q.value(0).toString();
    ui->user_name->setText(name);
    //查找所有空闲房间数量，用来初始化table
    //status=0为空闲，status=1为有客
    sql_select = "select count(roomid) from room where status=0";
    q.prepare(sql_select);
    q.exec();
    if(!q.next())
    {
        qDebug() << "db access err";
    }
    int num = q.value(0).toInt();
    //设置table行列数以及表头
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(num);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(150);
    QStringList header;
    header << "酒店名" << "地区" << "房间号" << "房间类型" << "原价" << "现价" << "评分" << "销售次数";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    sql_select = "select * from room where status=0";
    q.prepare(sql_select);
    q.exec();
    int index = 0;
    //逐行设置table内容
    while(q.next())
    {
        QString name = q.value(0).toString();
        QString roomid = q.value(1).toString();
        QString type = q.value(2).toString();
        float price = q.value(3).toFloat();
        float dis = q.value(5).toFloat();
        float score = q.value(6).toFloat();
        int sale_num = q.value(7).toInt();
        QSqlQuery qq;
        QString sql2 = "select * from hotel where hotelname=:hotelname";
        qq.prepare(sql2);
        qq.bindValue(":hotelname",name);
        qq.exec();
        if(!qq.next())
        {
            qDebug() << "db access err";
        }
        QString location = qq.value(2).toString();
        ui->tableWidget->setItem(index,0,new QTableWidgetItem(name));
        ui->tableWidget->setItem(index,1,new QTableWidgetItem(location));
        ui->tableWidget->setItem(index,2,new QTableWidgetItem(roomid));
        ui->tableWidget->setItem(index,3,new QTableWidgetItem(type));
        ui->tableWidget->setItem(index,4,new QTableWidgetItem(QString::number(price)));
        ui->tableWidget->setItem(index,5,new QTableWidgetItem(QString::number(price*dis)));
        ui->tableWidget->setItem(index,6,new QTableWidgetItem(QString::number(score)));
        ui->tableWidget->setItem(index,7,new QTableWidgetItem(QString::number(sale_num)));
        index += 1;
    }
    this->show();
}

void platform::on_pushButton_clicked()
{
       //跳转主界面
    emit show_main();
    this->close();
}

    //查询条件触发
void platform::on_query_clicked()
{
    QString city = ui->city_edit->text();
    QString location = ui->location_edit->text();
    QString type = ui->room_type->currentText();
    QString order = ui->order_type->currentText();
    QSqlQuery q;
    QString sql_select;
    //查询所有空闲房间
    if(type == "全部")
    {
        sql_select = "select count(roomid) from room natural join hotel where status=0 and city=:city and location=:location";
        q.prepare(sql_select);
        q.bindValue(":city",city);
        q.bindValue(":location",location);
        q.exec();
    }
    //查询某种类型的房间
    else
    {
        sql_select = "select count(roomid) from room natural join hotel where status=0 and city=:city and location=:location and type=:type";
        q.prepare(sql_select);
        q.bindValue(":city",city);
        q.bindValue(":location",location);
        q.bindValue(":type",type);
        q.exec();
    }
    if(!q.next())
    {
        qDebug() << "err";
    }
    int num = q.value(0).toInt();
    //初始化table行列数以及表头
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(num);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(150);
    QStringList header;
    header << "酒店名" << "地区" << "房间号" << "房间类型" << "原价" << "现价" << "评分" << "销售次数";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //全部房型，价格升序，优先高评价
    if(type == "全部" && order == "升序" && ui->rate->isChecked() == true)
    {
        sql_select = "select hotelname,price,discount,score,sale_num,type,roomid from room natural join hotel where status=0 and city=:city and location=:location order by price asc,score desc";
        q.prepare(sql_select);
        q.bindValue(":city",city);
        q.bindValue(":location",location);
        q.exec();
    }
    //全部房型，价格降序，优先高评价
    else if(type == "全部" && order == "降序" && ui->rate->isChecked() == true)
    {
        sql_select = "select hotelname,price,discount,score,sale_num,type,roomid from room natural join hotel where status=0 and city=:city and location=:location order by price desc,score desc";
        q.prepare(sql_select);
        q.bindValue(":city",city);
        q.bindValue(":location",location);
        q.exec();
    }
    //全部房型，价格升序
    else if(type == "全部" && order == "升序" && ui->rate->isChecked() == false)
    {
        sql_select = "select hotelname,price,discount,score,sale_num,type,roomid from room natural join hotel where status=0 and city=:city and location=:location order by price asc";
        q.prepare(sql_select);
        q.bindValue(":city",city);
        q.bindValue(":location",location);
        q.exec();
    }
    //全部房型，价格降序
    else if(type == "全部" && order == "降序" && ui->rate->isChecked() == false)
    {
        sql_select = "select hotelname,price,discount,score,sale_num,type,roomid from room natural join hotel where status=0 and city=:city and location=:location order by price desc";
        q.prepare(sql_select);
        q.bindValue(":city",city);
        q.bindValue(":location",location);
        q.exec();
    }
    //特定房型，价格升序，优先高评价
    else if(order == "升序" && ui->rate->isChecked() == true)
    {
        sql_select = "select hotelname,price,discount,score,sale_num,type,roomid from room natural join hotel where status=0 and city=:city and location=:location and type=:type order by price asc,score desc";
        q.prepare(sql_select);
        q.bindValue(":city",city);
        q.bindValue(":location",location);
        q.bindValue(":type",type);
        q.exec();
    }
    //特定房型，价格降序序，优先高评价
    else if(order == "降序" && ui->rate->isChecked() == true)
    {
        sql_select = "select hotelname,price,discount,score,sale_num,type,roomid from room natural join hotel where status=0 and city=:city and location=:location and type=:type order by price desc,score desc";
        q.prepare(sql_select);
        q.bindValue(":city",city);
        q.bindValue(":location",location);
        q.bindValue(":type",type);
        q.exec();
    }
    //特定房型，价格升序
    else if(order == "升序" && ui->rate->isChecked() == false)
    {
        sql_select = "select hotelname,price,discount,score,sale_num,type,roomid from room natural join hotel where status=0 and city=:city and location=:location and type=:type order by price asc";
        q.prepare(sql_select);
        q.bindValue(":city",city);
        q.bindValue(":location",location);
        q.bindValue(":type",type);
        q.exec();
    }
    //特定房型，价格降序
    else if(order == "降序" && ui->rate->isChecked() == false)
    {
        sql_select = "select hotelname,price,discount,score,sale_num,type,roomid from room natural join hotel where status=0 and city=:city and location=:location and type=:type order by price desc";
        q.prepare(sql_select);
        q.bindValue(":city",city);
        q.bindValue(":location",location);
        q.bindValue(":type",type);
        q.exec();
    }
    int index = 0;
    while(q.next())
    {
        QString name = q.value(0).toString();
        float price = q.value(1).toFloat();
        float dis = q.value(2).toFloat();
        float score = q.value(3).toFloat();
        int sale_num = q.value(4).toInt();
        QString room_type = q.value(5).toString();
        QString room_id = q.value(6).toString();
        ui->tableWidget->setItem(index,0,new QTableWidgetItem(name));
        ui->tableWidget->setItem(index,1,new QTableWidgetItem(location));
        ui->tableWidget->setItem(index,2,new QTableWidgetItem(room_id));
        ui->tableWidget->setItem(index,3,new QTableWidgetItem(room_type));
        ui->tableWidget->setItem(index,4,new QTableWidgetItem(QString::number(price)));
        ui->tableWidget->setItem(index,5,new QTableWidgetItem(QString::number(price*dis)));
        ui->tableWidget->setItem(index,6,new QTableWidgetItem(QString::number(score)));
        ui->tableWidget->setItem(index,7,new QTableWidgetItem(QString::number(sale_num)));
        index += 1;
    }
}

//预定按键触发，生成新订单插入到订单数据库中
void platform::on_order_clicked()
{
    int row = ui->tableWidget->currentItem()->row();
    QString name = ui->tableWidget->item(row,0)->text();
    QString room_id = ui->tableWidget->item(row,2)->text();
    float price = ui->tableWidget->item(row,5)->text().toFloat();
    emit show_room(this->phone,name,room_id,price);
    this->close();
}

void platform::on_my_order_clicked()
{
    //跳转我的订单
    emit show_order(this->phone);
    this->close();
}
