#include "passwordreset.h"
#include<QIcon>
#include <QPainter>
#include <QMessageBox>
#include "configuration.h"
#include "qdebug.h"
#include "ui_passwordreset.h"
#include<QTimer>

PasswordReset::PasswordReset(int id_,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PasswordReset),id(id_)
{
    ui->setupUi(this);
    init();
    md=new MyDatabase("PasswordReset"+QString::number(id));//数据库初始化
    db=md->getDatabase();
    query=QSqlQuery(db);

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&PasswordReset::blink );

    connect(ui->confirmlineEdit_4, &QLineEdit::textEdited,this, &PasswordReset::confirm );
    connect(ui->confirmtoolButton, &QToolButton::clicked, this, &PasswordReset::changePassword);
    connect(ui->canceltoolButton_2, &QToolButton::clicked, [&]{this->close();});
}

PasswordReset::~PasswordReset()
{
    qDebug()<<" passwor 析构 ";
    delete md;
    delete ui;
}

void PasswordReset::paintEvent(QPaintEvent *e)
{
    QPixmap pixmap = QPixmap(":/image/background/"+QString::number(ID_OF_BACKGROUND)+".jpg").scaled(this->size());
    QPainter painter(this);
    painter.drawPixmap(this->rect(),pixmap);
}

void PasswordReset::closeEvent(QCloseEvent* e)
{
    ui->curlineEdit->clear();
    ui->newlineEdit_3->clear();
    ui->confirmlineEdit_4->clear();
    ui->warninglabel_2->hide();
    e->accept();
}

void PasswordReset::init()
{
    this->setWindowTitle("修改密码");
    this->setWindowIcon(QIcon(":/image/icons48.png"));
//密码模式
    ui->curlineEdit->setEchoMode(QLineEdit::Password);ui->newlineEdit_3->setEchoMode(QLineEdit::Password);ui->confirmlineEdit_4->setEchoMode(QLineEdit::Password);
//按钮样式
    ui->confirmtoolButton->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);border-radius:5px;");    ui->canceltoolButton_2->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);border-radius:5px;");
    ui->warninglabel_2->hide();//警告信息
}

void PasswordReset::confirm(QString confirmPassword)
{
    if(confirmPassword!=ui->newlineEdit_3->text()){
        ui->warninglabel_2->show();
    }else{
        ui->warninglabel_2->hide();
    }
}

void PasswordReset::changePassword()
{//前后设置密码不一致，闪烁
    if(ui->confirmlineEdit_4->text()!=ui->newlineEdit_3->text()){
        timer->start(250);
        return;
    }
    QMessageBox::Button button  = QMessageBox::question(this,"确认修改","是否确认修改密码");
    if(button==QMessageBox::Yes){
        QString sql = "SELECT username FROM `user` WHERE `id`="+ QString::number(id)+ " AND pwd='"+ui->curlineEdit->text()+ "'";
        query.exec(sql);
        if(query.next()){
            sql = "UPDATE `user` SET pwd='"+ui->confirmlineEdit_4->text() + "' WHERE `id`= "+ QString::number(id);
            if(query.exec(sql)){QMessageBox::information(this,"修改密码成功","修改密码成功");return;}
        }
        else{
            QMessageBox::information(this,"修改密码失败","当前的账号密码输入错误");
            return;
        }
    }
}

void PasswordReset::blink()
{
    if(blinkCnt++ == 10){timer->stop();blinkCnt=0;confirm(ui->confirmlineEdit_4->text());return;}
    if(ui->warninglabel_2->isHidden())  ui->warninglabel_2->show();
    else    ui->warninglabel_2->hide();
}
