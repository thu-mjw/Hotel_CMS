#-------------------------------------------------
#
# Project created by QtCreator 2018-07-27T23:28:44
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hotel
TEMPLATE = app
# CONFIG += qaxcontainer

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    login.cpp \
    hotelregister.cpp \
    hotellogin.cpp \
    hotelshow.cpp \
    platform.cpp \
    regi.cpp \
    addroom.cpp \
    saledetail.cpp \
    ordercontroller.cpp \
    myorder.cpp \
    score.cpp \
    root_regi.cpp \
    root_login.cpp \
    hotelconfirm.cpp \
    showroom.cpp \
    showpay.cpp

HEADERS += \
        mainwindow.h \
    login.h \
    hotelregister.h \
    hotellogin.h \
    hotelshow.h \
    platform.h \
    regi.h \
    addroom.h \
    saledetail.h \
    ordercontroller.h \
    myorder.h \
    score.h \
    root_regi.h \
    root_login.h \
    hotelconfirm.h \
    showroom.h \
    showpay.h

FORMS += \
        mainwindow.ui \
    login.ui \
    hotelregister.ui \
    hotellogin.ui \
    hotelshow.ui \
    platform.ui \
    regi.ui \
    addroom.ui \
    saledetail.ui \
    ordercontroller.ui \
    myorder.ui \
    score.ui \
    root_regi.ui \
    root_login.ui \
    hotelconfirm.ui \
    showroom.ui \
    showpay.ui

RESOURCES += \
    picture.qrc\
    icon.qrc

RC_FILE = Hotel_CMS.rc
