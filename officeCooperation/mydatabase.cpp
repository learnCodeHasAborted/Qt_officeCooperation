#include "mydatabase.h"

MyDatabase::MyDatabase(QString name)
{
    db = QSqlDatabase::addDatabase("QMYSQL",name);
    // 数据库连接需要设置的信息
    db.setHostName("***"); // 数据库服务器IP，把 *** 改成自己的数据库 IP 地址，下面也要改
    db.setDatabaseName("***");// 数据库名
    db.setUserName("***");// 用户名
    db.setPassword("***");// 密码
    db.setPort(3306);// 端口号
    db.open();
}

QSqlDatabase MyDatabase::getDatabase(){
    return db;
}
