#ifndef TODOLIST_H
#define TODOLIST_H

#include <QWidget>
#include"mydatabase.h"
#include<QMap>
#include"todo.h"

namespace Ui {
class ToDoList;
}

class ToDoList : public QWidget
{
    Q_OBJECT

public:
    explicit ToDoList(int id,QWidget *parent = nullptr);
    ~ToDoList();

    int uid;
    MyDatabase* md=nullptr;
    QSqlDatabase db;
    QSqlQuery query;
    QMap<int , ToDo*> things;

    QTimer* timer=nullptr;

private:
    Ui::ToDoList *ui;
    void showTodo(int id,QString pre);
public slots:
    void complete(int uid, int IP);
};

#endif // TODOLIST_H
