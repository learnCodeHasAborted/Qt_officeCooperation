#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include<QMessageBox>
#include"mydatabase.h"
#include"mainwindow.h"
#include<QPainter>
#include<QPixmap>
#include<QPalette>
#include"configuration.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    init();
    ui->username->setFocus();//默认焦点
    //默认回车确认登录
    ui->loginBtn->setShortcut(Qt::Key_Enter);
    ui->loginBtn->setShortcut(Qt::Key_Return);
}


login::~login()
{
    delete ui;
}

void login::init()
{
    this->setWindowTitle("登录");
    this->setWindowIcon(QIcon(":/image/icons48.png"));
//背景、字体 颜色
    ui->loginBtn->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);border-radius:5px;");
    ui->registerBtn->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);border-radius:5px;");
}

void login::paintEvent(QPaintEvent *event)
{
    QPixmap pixmap = QPixmap(":/image/background/"+QString::number(ID_OF_BACKGROUND)+".jpg").scaled(this->size());
    QPainter painter(this);
    painter.drawPixmap(this->rect(), pixmap);
}

void login::verify(){
    username=ui->username->text();pwd=ui->pwd->text();
    //判断有效输入
    if(username==""||pwd==""){
        QMessageBox::StandardButton dialog=QMessageBox::critical(this,"登录失败","用户名或密码不能为空");
        return;
    }
    MyDatabase md("log"+username);
    QSqlDatabase db=md.getDatabase();

    QSqlQuery  query(db);
    QString sql = "select `id`,`username`,`icon`,`background` from `user` "
                  "where binary `username`='"+username+"' and binary `pwd`='"+pwd+"' and state =0";
    query.exec(sql);

    //登录成功
    if(query.next()){
        query.first();
        int id=query.value(0).toInt();
        QString username=query.value(1).toString();
        ID_OF_ICON = query.value(2).toInt();
        ID_OF_BACKGROUND = query.value(3).toInt();
        //修改登录状态为上线
        query.exec("UPDATE `user` SET state=1 WHERE id="+QString::number(id));
        emit login_success_signals(id,username);
    }//失败
    else{
        QMessageBox::StandardButton dialog=QMessageBox::critical(this,"登录失败","可能的原因有：\n1、用户名不存在\n2、密码错误\n3、账号已在线，无法重复登录");
    }

}

void login::showRegister(){
    emit new_register_signals();
}



