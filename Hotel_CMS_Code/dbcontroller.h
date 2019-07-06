#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class dbController
{
public:
    dbController();
    QSqlDatabase db;
};

#endif // DBCONTROLLER_H
