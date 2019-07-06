#include "addroom.h"
#include "ui_addroom.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFileDialog>

addRoom::addRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addRoom)
{
    ui->setupUi(this);
}

addRoom::~addRoom()
{
    delete ui;
}

void addRoom::on_back_clicked()
{
    emit show_hotel(hotel_name);
    this->close();
}
//添加房间
void addRoom::on_add_button_clicked()
{
    int flag = 0;
    QString roomid = ui->room_id_edit->text();
    QString price = ui->room_price_edit->text();
    QString discount = ui->discount_edit->text();
    float dis = 1.0;
    QString type = ui->comboBox->currentText();
    QString describe = ui->textEdit_des->toPlainText();
    QString pic_url = ui->lineEdit_pic_url->text();
    if(roomid.isEmpty())
    {
        flag = 1;
        ui->err_no->setText("房间号不能为空!");
    }
    if(price.isEmpty())
    {
        flag = 1;
        ui->err_price->setText("价格不能为空!");
    }
    if(!discount.isEmpty())
    {
        dis = discount.toFloat();
    }
    if(flag)
    {
        return ;
    }
    QSqlQuery q;
    QString sql_select = "insert into room values(?,?,?,?,?,?,?,?,?,?)";
    q.prepare(sql_select);
    q.addBindValue(this->hotel_name);
    q.addBindValue(roomid);
    q.addBindValue(type);
    q.addBindValue(price.toFloat());
    q.addBindValue(0);
    q.addBindValue(dis);
    q.addBindValue(0.0);
    q.addBindValue(0);
    q.addBindValue(describe);
    q.addBindValue(pic_url);
    q.exec();
    ui->info_succ->setText("添加成功!");
    ui->room_id_edit->setText("");
    ui->room_price_edit->setText("");
    ui->discount_edit->setText("");
    ui->lineEdit_pic_url->setText("");
    ui->textEdit_des->setText("");
}
//刷新显示此界面
void addRoom::reshow(QString id)
{
    hotel_name = id;
    ui->info_succ->setText("");
    ui->room_id_edit->setText("");
    ui->room_price_edit->setText("");
    ui->discount_edit->setText("");
    ui->lineEdit_pic_url->setText("");
    ui->textEdit_des->setText("");
    this->show();
}
//设置图片路径
void addRoom::on_toolButton_clicked()
{
    QString folder_path = QFileDialog::getOpenFileName(this,"请选择路径...","./");
    ui->lineEdit_pic_url->setText(folder_path);
}
