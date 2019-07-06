#ifndef PLATFORM_H
#define PLATFORM_H

#include <QWidget>

namespace Ui {
class platform;
}

class platform : public QWidget
{
    Q_OBJECT

public:
    explicit platform(QWidget *parent = 0);
    ~platform();
    QString phone;

private slots:
    void reshow(QString);

    void on_pushButton_clicked();

    void on_query_clicked();

    void on_order_clicked();

    void on_my_order_clicked();

signals:
    void show_main();
    void show_room(QString,QString,QString,float);
    void show_order(QString);

private:
    Ui::platform *ui;
};

#endif // PLATFORM_H
