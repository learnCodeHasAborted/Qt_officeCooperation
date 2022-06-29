#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QTime>
#include<QTimeEdit>
#include<QtSql>
#include <qsqldatabase.h>
#include <QSortFilterProxyModel>
#include <QHeaderView>
#include <QSqlTableModel>
#include "mydatabase.h"


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(int id,QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pBton_shezhi_clicked();
    void on_pBton_cancel_clicked();

private:
    Ui::Dialog *ui;
public:

    MyDatabase* md=nullptr;
    QSqlDatabase db;

    int uid;//用户id
    QTime setTime[7][8];        //星期一到星期天的时间设置
    QString setEvent[7][4];

    QStringList IPlist;         //事件列表

};

#endif // DIALOG_H
