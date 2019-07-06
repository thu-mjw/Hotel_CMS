#ifndef ADDROOM_H
#define ADDROOM_H

#include <QWidget>

namespace Ui {
class addRoom;
}

class addRoom : public QWidget
{
    Q_OBJECT

public:
    explicit addRoom(QWidget *parent = 0);
    ~addRoom();
    QString hotel_name;

private slots:
    void on_back_clicked();

    void on_add_button_clicked();
    void reshow(QString);

    void on_toolButton_clicked();

signals:
    void show_hotel(QString);

private:
    Ui::addRoom *ui;
};

#endif // ADDROOM_H
