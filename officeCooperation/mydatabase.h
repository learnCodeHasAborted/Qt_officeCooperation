#ifndef MYDATABASE_H
#define MYDATABASE_H

#include<QSqlQuery>
#include<QSqlDatabase>

class MyDatabase
{
public:
    MyDatabase(QString name);
    QSqlDatabase getDatabase();
private:
    QSqlDatabase db;
};

#endif // MYDATABASE_H
