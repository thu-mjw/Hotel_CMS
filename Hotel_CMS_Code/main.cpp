#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "login.h"
#include "regi.h"
#include "hotellogin.h"
#include "hotelregister.h"
#include "hotelshow.h"
#include "platform.h"
#include "addroom.h"
#include "saledetail.h"
#include "ordercontroller.h"
#include "myorder.h"
#include "score.h"
#include "hotelconfirm.h"
#include "root_login.h"
#include "root_regi.h"
#include "showroom.h"
#include "showpay.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName("localhost");
    //设置数据库路径
    db.setDatabaseName("C:/Hotel_CMS/hotel.db");
    if(!db.open())
    {
        qDebug() << "db not open!";
    }
    MainWindow m;
    //设置主窗口标题
    m.setWindowTitle("Hotel_CMS");
    //设置窗体和标题栏透明
    m.setWindowFlags(Qt::FramelessWindowHint);
    m.setAttribute(Qt::WA_TranslucentBackground,true);
    login l;
    l.setWindowFlags(Qt::FramelessWindowHint);
    l.setAttribute(Qt::WA_TranslucentBackground,true);
    regi r;
    r.setWindowFlags(Qt::FramelessWindowHint);
    r.setAttribute(Qt::WA_TranslucentBackground,true);
    platform p;
    p.setWindowFlags(Qt::FramelessWindowHint);
    p.setAttribute(Qt::WA_TranslucentBackground,true);
    hotelLogin hl;
    hl.setWindowFlags(Qt::FramelessWindowHint);
    hl.setAttribute(Qt::WA_TranslucentBackground,true);
    hotelRegister hr;
    hr.setWindowFlags(Qt::FramelessWindowHint);
    hr.setAttribute(Qt::WA_TranslucentBackground,true);
    hotelShow hs;
    hs.setWindowFlags(Qt::FramelessWindowHint);
    hs.setAttribute(Qt::WA_TranslucentBackground,true);
    addRoom ar;
    ar.setWindowFlags(Qt::FramelessWindowHint);
    ar.setAttribute(Qt::WA_TranslucentBackground,true);
    saleDetail sd;
    sd.setWindowFlags(Qt::FramelessWindowHint);
    sd.setAttribute(Qt::WA_TranslucentBackground,true);
    orderController oc;
    oc.setWindowFlags(Qt::FramelessWindowHint);
    oc.setAttribute(Qt::WA_TranslucentBackground,true);
    myOrder mo;
    mo.setWindowFlags(Qt::FramelessWindowHint);
    mo.setAttribute(Qt::WA_TranslucentBackground,true);
    score s;
    s.setWindowFlags(Qt::FramelessWindowHint);
    s.setAttribute(Qt::WA_TranslucentBackground,true);
    showRoom sr;
    sr.setWindowFlags(Qt::FramelessWindowHint);
    sr.setAttribute(Qt::WA_TranslucentBackground,true);
    root_login rl;
    rl.setWindowFlags(Qt::FramelessWindowHint);
    rl.setAttribute(Qt::WA_TranslucentBackground,true);
    root_regi rr;
    rr.setWindowFlags(Qt::FramelessWindowHint);
    rr.setAttribute(Qt::WA_TranslucentBackground,true);
    hotelConfirm hc;
    hc.setWindowFlags(Qt::FramelessWindowHint);
    hc.setAttribute(Qt::WA_TranslucentBackground,true);
    showPay sp;
    sp.setWindowFlags(Qt::FramelessWindowHint);
    sp.setAttribute(Qt::WA_TranslucentBackground,true);
    //用户登录界面
    QObject::connect(&l,SIGNAL(show_regi()),&r,SLOT(reshow()));     //跳转用户注册
    QObject::connect(&l,SIGNAL(show_platform(QString)),&p,SLOT(reshow(QString)));     //跳转平台
    QObject::connect(&l,SIGNAL(show_main()),&m,SLOT(reshow()));     //跳转主界面
    //用户注册界面
    QObject::connect(&r,SIGNAL(show_platform(QString)),&p,SLOT(reshow(QString)));     //跳转平台
    QObject::connect(&r,SIGNAL(show_login()),&l,SLOT(reshow()));    //跳转用户登录
    QObject::connect(&r,SIGNAL(show_main()),&m,SLOT(reshow()));     //跳转主界面
    //主界面
    QObject::connect(&m,SIGNAL(show_login()),&l,SLOT(reshow()));    //跳转用户登录
    QObject::connect(&m,SIGNAL(show_regi()),&r,SLOT(reshow()));     //跳转用户注册
    QObject::connect(&m,SIGNAL(show_hotel_login()),&hl,SLOT(reshow()));     //跳转酒店经理登录
    QObject::connect(&m,SIGNAL(show_hotel_regi()),&hr,SLOT(reshow()));      //跳转酒店注册
    QObject::connect(&m,SIGNAL(show_root_login()),&rl,SLOT(reshow()));      //跳转审核登录
    QObject::connect(&m,SIGNAL(show_root_register()),&rr,SLOT(reshow()));   //跳转审核注册
    //酒店登录
    QObject::connect(&hl,SIGNAL(show_hotel(QString)),&hs,SLOT(reshow(QString)));      //跳转酒店界面
    QObject::connect(&hl,SIGNAL(show_main()),&m,SLOT(reshow()));                //跳转主界面
    //酒店注册
    QObject::connect(&hr,SIGNAL(show_main()),&m,SLOT(reshow()));                //跳转主界面
    //酒店显示
    QObject::connect(&hs,SIGNAL(show_main()),&m,SLOT(reshow()));        //跳转主界面
    QObject::connect(&hs,SIGNAL(show_add_room(QString)),&ar,SLOT(reshow(QString)));     //跳转添加房间界面
    QObject::connect(&hs,SIGNAL(show_detail(QString)),&sd,SLOT(reshow(QString)));       //跳转销售详情界面
    QObject::connect(&hs,SIGNAL(show_order(QString)),&oc,SLOT(reshow(QString)));        //跳转订单界面
    //平台界面
    QObject::connect(&p,SIGNAL(show_main()),&m,SLOT(reshow()));         //跳转主界面
    QObject::connect(&p,SIGNAL(show_room(QString,QString,QString,float)),&sr,SLOT(reshow(QString,QString,QString,float)));  //跳转房间信息界面
    QObject::connect(&p,SIGNAL(show_order(QString)),&mo,SLOT(reshow(QString)));     //跳转我的订单
    //添加房间界面
    QObject::connect(&ar,SIGNAL(show_hotel(QString)),&hs,SLOT(reshow(QString)));      //跳转酒店界面
    //销售详情界面
    QObject::connect(&sd,SIGNAL(show_hotel(QString)),&hs,SLOT(reshow(QString)));      //跳转酒店界面
    //订单管理界面
    QObject::connect(&oc,SIGNAL(show_hotel(QString)),&hs,SLOT(reshow(QString)));      //跳转酒店界面
    QObject::connect(&oc,SIGNAL(show_self(QString)),&oc,SLOT(reshow(QString)));         //刷新界面
    //用户订单界面
    QObject::connect(&mo,SIGNAL(show_main()),&m,SLOT(reshow()));                //返回主界面
    QObject::connect(&mo,SIGNAL(show_platform(QString)),&p,SLOT(reshow(QString)));  //跳到平台
    QObject::connect(&mo,SIGNAL(show_score(QString,QString,QString)),&s,SLOT(reshow(QString,QString,QString)));     //跳转评分界面
    QObject::connect(&mo,SIGNAL(show_pay(QString,QString,QString)),&sp,SLOT(reshow(QString,QString,QString)));      //跳转支付界面
    QObject::connect(&mo,SIGNAL(show_self(QString)),&mo,SLOT(reshow(QString)));     //刷新
    //用户评分界面
    QObject::connect(&s,SIGNAL(show_my_order(QString)),&mo,SLOT(reshow(QString)));      //跳转用户订单界面
    //审核注册界面
    QObject::connect(&rr,SIGNAL(show_confirm()),&hc,SLOT(reshow()));                //跳转酒店审核
    QObject::connect(&rr,SIGNAL(show_main()),&m,SLOT(reshow()));                    //跳转主界面
    //审核登录界面
    QObject::connect(&rl,SIGNAL(show_confirm()),&hc,SLOT(reshow()));                //跳转酒店审核
    QObject::connect(&rl,SIGNAL(show_main()),&m,SLOT(reshow()));                    //跳转主界面
    //显示房间信息界面
    QObject::connect(&sr,SIGNAL(show_order(QString)),&mo,SLOT(reshow(QString)));    //跳转我的订单界面
    QObject::connect(&sr,SIGNAL(show_platform(QString)),&p,SLOT(reshow(QString)));  //跳转平台界面
    //支付界面
    QObject::connect(&sp,SIGNAL(show_order(QString)),&mo,SLOT(reshow(QString)));    //跳转订单界面
    //审核酒店界面
    QObject::connect(&hc,SIGNAL(show_main()),&m,SLOT(reshow()));                    //跳转主界面
    QObject::connect(&hc,SIGNAL(show_self()),&hc,SLOT(reshow()));                   //刷新
    m.show();
    return a.exec();
}
