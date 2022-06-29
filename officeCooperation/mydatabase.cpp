#include "mydatabase.h"

MyDatabase::MyDatabase(QString name)
{
    db = QSqlDatabase::addDatabase("QMYSQL",name);
    // 数据库连接需要设置的信息
    db.setHostName("49.235.84.252"); // 数据库服务器IP
    db.setDatabaseName("officeCooperation");// 数据库名
//    db.setDatabaseName("test");// 数据库名
    db.setUserName("guest");// 用户名
    db.setPassword("DOvBFEtrf9/d");// 密码
    db.setPort(3306);// 端口号
    db.open();
}

QSqlDatabase MyDatabase::getDatabase(){
    return db;
}
