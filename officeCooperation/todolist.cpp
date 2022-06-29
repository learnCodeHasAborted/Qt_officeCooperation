#include "todolist.h"
#include "ui_todolist.h"
#include<QTextBrowser>
#include<QMessageBox>
#include<QTimer>
#include<QDebug>

ToDoList::ToDoList(int id, QWidget *parent) :
    QWidget(parent),
    uid(id),ui(new Ui::ToDoList)
{
    ui->setupUi(this);
    this->setWindowTitle("待办事项");
    this->setWindowIcon(QIcon(":/image/icons48.png"));
    md=new MyDatabase("todolist"+QString::number(id));//数据库初始化
    db=md->getDatabase();
    query=QSqlQuery(db);
    showTodo(uid,"");
}

ToDoList::~ToDoList()
{
    delete ui;
}

void ToDoList::showTodo(int id, QString pre)
{
    ui->listWidget->clear();
    if(pre!=""){query.exec(pre);}//删除
    QString sql = "SELECT `start`,`end`,`event`,`IP` FROM `timetable` WHERE uid="+QString::number(id);
    qDebug()<<sql;
    query.exec(sql);
    int colorId = 0;
    while(query.next()){
        QString start=query.value(0).toString();
        QString end= query.value(1).toString();
        QString event=query.value(2).toString();
        int IP=query.value(3).toInt();
        qDebug()<<IP;
        ToDo* tb = new ToDo(id,IP,start,end,event,colorId++);
        connect(tb,&ToDo::forwardComplete, this, &ToDoList::complete );
        things.insert(id,tb);
        QListWidgetItem *item=new QListWidgetItem(ui->listWidget);
        item->setSizeHint(QSize(ui->listWidget->width()-5,80));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,tb);
        tb->show();
    }
}

void ToDoList::complete(int uid, int IP)
{
    QMessageBox::Button button = QMessageBox::question(this,"","是否完成该任务");
    if(button==QMessageBox::Yes){
        QString sql = "delete  FROM `timetable` WHERE uid="+QString::number(uid)+" and IP="+QString::number(IP);
        showTodo(uid,sql);
    }
}
