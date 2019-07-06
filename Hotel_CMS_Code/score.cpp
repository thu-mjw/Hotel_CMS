#include "score.h"
#include "ui_score.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
score::score(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::score)
{
    ui->setupUi(this);
}

score::~score()
{
    delete ui;
}

void score::reshow(QString phone, QString name, QString roomid)
{
    this->phone = phone;
    this->name = name;
    this->roomid = roomid;
    ui->score_info->setText("");
    this->show();
}

void score::on_pushButton_clicked()
{
    emit show_my_order(this->phone);
    this->close();
}

//评分按键触发
void score::on_pushButton_2_clicked()
{
    int sc = ui->comboBox->currentText().toInt();
    QSqlQuery q;
    //查找该房间的之前评分信息
    QString sql = "select score,sale_num,hotel.hotelname from room,myorder,hotel where hotel.hotelname=myorder.hotelname and hotel.hotelname=room.hotelname and hotel.hotelname=:name and myorder.roomid=room.roomid and myorder.roomid=:roomid";
    q.prepare(sql);
    q.bindValue(":name",this->name);
    q.bindValue(":roomid",this->roomid);
    q.exec();
    if(!q.next())
    {
        qDebug() << "db access err";
    }
    float old_score = q.value(0).toFloat();
    int sale_num = q.value(1).toInt();
    QString name = q.value(2).toString();
    float new_score = (old_score+sc)/sale_num;
    //更新该房间的评分信息
    QString sql_select = "update room set score=:score where room.hotelname=:hotelname and room.roomid=:roomid";
    q.prepare(sql_select);
    q.bindValue(":score",new_score);
    q.bindValue(":hotelid",name);
    q.bindValue(":roomid",this->roomid);
    q.exec();
    ui->score_info->setText("评价成功!");
}
