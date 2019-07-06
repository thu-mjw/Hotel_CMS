#include "saledetail.h"
#include "ui_saledetail.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
saleDetail::saleDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::saleDetail)
{
    ui->setupUi(this);
}

saleDetail::~saleDetail()
{
    delete ui;
}

void saleDetail::on_pushButton_2_clicked()
{
    emit show_hotel(hotel_name);
    this->close();
}

void saleDetail::reshow(QString id)
{
    ui->lineEdit->setText("");
    ui->set_info->setText("");
    hotel_name = id;
    ui->file_info->setText("");
    QSqlQuery q;
    //查询所有已完成的订单数量
    QString sql_select = "select count(phone) from myorder,hotel where myorder.status='14' and myorder.hotelname=:hotelname";
    q.prepare(sql_select);
    q.bindValue(":hotelname",this->hotel_name);
    q.exec();
    if(!q.next())
    {
        qDebug() << "db access err";
    }
    int num = q.value(0).toInt();
    //初始化table的行列数以及表头
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(num);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(150);
    QStringList header;
    header << "房间号" << "评分" << "销售次数";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    sql_select = "select room.roomid,score,sale_num from room,hotel,myorder where myorder.status='14' and myorder.roomid=room.roomid and myorder.hotelname=hotel.hotelname and hotel.hotelname=room.hotelname and hotel.hotelname=:hotelname";
    q.prepare(sql_select);
    q.bindValue(":hotelname",this->hotel_name);
    q.exec();
    int index = 0;
    while(q.next())
    {
        QString room_id = q.value(0).toString();
        float score = q.value(1).toFloat();
        int sale_num = q.value(2).toInt();
        ui->tableWidget->setItem(index,0,new QTableWidgetItem(room_id));
        ui->tableWidget->setItem(index,1,new QTableWidgetItem(QString::number(score)));
        ui->tableWidget->setItem(index,2,new QTableWidgetItem(QString::number(sale_num)));
        index += 1;
    }
    this->show();
}

//将销售情况导入到csv文件中
void saleDetail::on_pushButton_clicked()
{
    QString file_name = ui->lineEdit->text()+"/sale_detail.csv";
    qDebug() << file_name;
    QFile file(file_name);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << "roomid,score,sale numbers\n";
    int rows = ui->tableWidget->rowCount();
    int cols = ui->tableWidget->columnCount();
    for(int i = 0;i < rows;i++)
    {
        for(int j = 0;j < cols;j++)
        {
            if(ui->tableWidget->item(i,j) != NULL)
            {
                if(j == cols-1)
                {
                    out << ui->tableWidget->item(i,j)->text();
                }
                else
                {
                    out << ui->tableWidget->item(i,j)->text() << ",";
                }
            }
        }
        out << "\n";
    }
    file.close();
    ui->file_info->setText("导出csv成功!");
}

//设置存储路径
void saleDetail::on_toolButton_clicked()
{
    QString folder_path = QFileDialog::getExistingDirectory(this,"请选择保存路径...","./");
    if(folder_path.isEmpty())
    {
        QMessageBox::information(NULL, "error", "存储路径选择错误，请重新选择!");
    }
    else
    {
        ui->lineEdit->setText(folder_path);
    }
}


