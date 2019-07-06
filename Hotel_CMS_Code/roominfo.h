#ifndef ROOMINFO_H
#define ROOMINFO_H

#include <QWidget>

namespace Ui {
class roomInfo;
}

class roomInfo : public QWidget
{
    Q_OBJECT

public:
    explicit roomInfo(QWidget *parent = 0);
    ~roomInfo();

private:
    Ui::roomInfo *ui;
};

#endif // ROOMINFO_H
