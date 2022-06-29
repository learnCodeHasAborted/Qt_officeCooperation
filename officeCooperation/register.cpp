#include "register.h"
#include "ui_register.h"
#include<QMessageBox>
#include "login.h"
#include"mydatabase.h"
#include<QDebug>
#include<QPainter>
#include"configuration.h"

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    init();
    ui->usernameLine->setFocus();
    ui->confirmBtn->setShortcut(Qt::Key_Enter);
    ui->confirmBtn->setShortcut(Qt::Key_Return);

}

Register::~Register()
{
    qDebug()<<"delete register ";
    delete ui;
}

void Register::paintEvent(QPaintEvent *event)
{
    QPixmap pixmap = QPixmap(":/image/background/"+QString::number(ID_OF_BACKGROUND)+".jpg").scaled(this->size());
    QPainter painter(this);
    painter.drawPixmap(this->rect(), pixmap);
}

void Register::init()
{
    this->setWindowTitle("注册");
    this->setWindowIcon(QIcon(":/image/icons48.png") );

    ui->confirmBtn->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);border-radius:5px;");
    ui->pushButton_2->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);border-radius:5px;");
}

void Register::verify(){
    //判断有效输入
    if(username==""||pwd==""){
        qDebug()<<"ZHUCE SHIBAI"<<Qt::endl;
        QMessageBox::StandardButton dialog=QMessageBox::critical(this,"注册失败","用户名或密码不能为空");
        return;
    }
    //连接数据库查询是否已经存在用户名
    MyDatabase md("reg"+username);
    QSqlDatabase db=md.getDatabase();

    QSqlQuery  query(db);
    QString sql = "select `username` from `user` "
                  "where  binary `username`='"+username+"' ";
    query.exec(sql);
    //用户已存在
    if(query.next()){
        QMessageBox::StandardButton dialog=QMessageBox::critical(this,"注册失败","用户名已存在");
    }
    else{//数据库添加username和pwd
        QString sql = " INSERT INTO `user` (username,pwd,state,icon,background) VALUES('"+username+"','"+pwd+"',0,1,3)";
        //执行成功
        if(query.exec(sql)){
            QMessageBox::StandardButton dialog=QMessageBox::information(this,"注册成功","请返回登录界面登录");
        }
        else{
            QMessageBox::StandardButton dialog=QMessageBox::critical(this,"注册失败","出现未知错误,请您重新点击注册按钮");
        }
    }
}

void Register::getUsername(QString text){
    this->username=text;
}

void Register::getPwd(QString text){
    this->pwd=text;
}

void Register::showLogin(){
    emit back_login_signals();
}
