#ifndef SHOWROOM_H
#define SHOWROOM_H

#include <QWidget>

namespace Ui {
class showRoom;
}

class showRoom : public QWidget
{
    Q_OBJECT

public:
    explicit showRoom(QWidget *parent = 0);
    ~showRoom();
    QString phone;
    QString name;
    QString roomid;
    float price;

private slots:
    void on_pushButton_2_clicked();
    void reshow(QString,QString,QString,float);

    void on_pushButton_clicked();

signals:
    void show_platform(QString);
    void show_order(QString);

private:
    Ui::showRoom *ui;
};

#endif // SHOWROOM_H
