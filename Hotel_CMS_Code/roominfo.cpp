#include "roominfo.h"
#include "ui_roominfo.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
roomInfo::roomInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::roomInfo)
{
    ui->setupUi(this);
}

roomInfo::~roomInfo()
{
    delete ui;
}
