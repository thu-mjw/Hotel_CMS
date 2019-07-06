#include "hotelconfirm.h"
#include "ui_hotelconfirm.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
hotelConfirm::hotelConfirm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::hotelConfirm)
{
    ui->setupUi(this);
}

hotelConfirm::~hotelConfirm()
{
    delete ui;
}

void hotelConfirm::on_pushButton_clicked()
{
    int row = ui->tableWidget->currentItem()->row();
    QString name = ui->tableWidget->item(row,0)->text();
    QSqlQuery q;
    //从数据库hotel_regi载入
    QString sql_select = "select * from hotel_regi where hotelname=:hotelname";
    q.prepare(sql_select);
    q.bindValue(":hotelname",name);
    q.exec();
    if(!q.next())
    {
        qDebug() << "db access err";
    }
    QString city = q.value(1).toString();
    QString location = q.value(2).toString();
    QString manager = q.value(3).toString();
    QString pwd = q.value(4).toString();
    //写入数据库hotel
    QString sql_insert = "insert into hotel values(?,?,?,?,?)";
    q.prepare(sql_insert);
    q.addBindValue(name);
    q.addBindValue(city);
    q.addBindValue(location);
    q.addBindValue(manager);
    q.addBindValue(pwd);
    q.exec();
    QString sql_del = "delete from hotel_regi where hotelname=:hotelname";
    q.prepare(sql_del);
    q.bindValue(":hotelname",name);
    q.exec();
    ui->result->setText("注册已通过");
    this->close();
    emit show_self();
}

void hotelConfirm::on_pushButton_2_clicked()
{
    //跳转主界面
    emit show_main();
    this->close();
}

void hotelConfirm::reshow()
{
    ui->result->setText("");
    QSqlQuery q;
    QString sql_select = "select count(hotelname) from hotel_regi";
    q.prepare(sql_select);
    q.exec();
    if(!q.next())
    {
        qDebug() << "db access err";
    }
    int num = q.value(0).toInt();
    //设置table行列数以及表头
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(num);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(150);
    QStringList header;
    header << "酒店名" << "城市" << "地区" << "经理手机号码";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    sql_select = "select * from hotel_regi";
    q.prepare(sql_select);
    q.exec();
    int index = 0;
    //逐行设置table内容
    while(q.next())
    {
        QString name = q.value(0).toString();
        QString city = q.value(1).toString();
        QString location = q.value(2).toString();
        QString manager = q.value(3).toString();
        ui->tableWidget->setItem(index,0,new QTableWidgetItem(name));
        ui->tableWidget->setItem(index,1,new QTableWidgetItem(city));
        ui->tableWidget->setItem(index,2,new QTableWidgetItem(location));
        ui->tableWidget->setItem(index,3,new QTableWidgetItem(manager));
        index += 1;
    }
    this->show();
}
