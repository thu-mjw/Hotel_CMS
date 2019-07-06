#ifndef SCORE_H
#define SCORE_H

#include <QWidget>

namespace Ui {
class score;
}

class score : public QWidget
{
    Q_OBJECT

public:
    explicit score(QWidget *parent = 0);
    ~score();
    QString phone;
    QString name;
    QString roomid;

signals:
    void show_my_order(QString);

private slots:
    void reshow(QString,QString,QString);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::score *ui;
};

#endif // SCORE_H
