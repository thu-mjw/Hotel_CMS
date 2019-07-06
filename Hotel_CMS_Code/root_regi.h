#ifndef ROOT_REGI_H
#define ROOT_REGI_H

#include <QWidget>

namespace Ui {
class root_regi;
}

class root_regi : public QWidget
{
    Q_OBJECT

public:
    explicit root_regi(QWidget *parent = 0);
    ~root_regi();

private slots:
    void reshow();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void show_main();
    void show_confirm();

private:
    Ui::root_regi *ui;
};

#endif // ROOT_REGI_H
