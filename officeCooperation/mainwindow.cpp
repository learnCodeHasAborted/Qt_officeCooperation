#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QListWidget"
#include"QListWidgetItem"
#include"friendwidget.h"
#include<QHostAddress>
#include<QMessageBox>
#include<QMap>
#include"chatclient.h"
#include<QDebug>
#include<QDateTime>
#include<QPixmap>
#include<QPainter>
#include<QFileInfo>
#include"addfriend.h"
#include"login.h"
#include"mainsiderbar.h"
#include"configuration.h"
#include<QHostAddress>

//#include<QTimer>

MainWindow::MainWindow(int id_,QString username_, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),id(id_),username(username_)
{
    ui->setupUi(this);
    init();
    md=new MyDatabase("main"+username);//数据库初始化
    db=md->getDatabase();
    query=QSqlQuery(db);
    myConnect();//连接服务器，chatServer和fileServer
    timer=new QTimer(this);
    timer->start(2000);//两秒后判断是否连接成功
    connect(timer,&QTimer::timeout, this,&MainWindow::isConnected);
    showFriends();//显示联系人
    //界面功能
    connect(ui->searchlineEdit,&QLineEdit::textEdited, this, &MainWindow::search );//搜索已有联系人
    connect(ui->addtoolButton, &QPushButton::clicked, this,&MainWindow::add_friend_slots); //添加联系人
}

MainWindow::~MainWindow()
{
    delete chatSocket;delete fileSocket;delete md;delete msb;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* e){
    if(query.exec("UPDATE `user` SET state=0 WHERE id="+QString::number(id))){
        qDebug()<<"UPDATE `user` SET state=0 WHERE id="+QString::number(id);
    }
    noticify("disconnected");
    QString filedis = "disconnected"+split+username;
    if(fileSocket->isWritable())
        fileSocket->write(filedis.toUtf8());
    chatSocket->disconnectFromHost();
    fileSocket->disconnectFromHost();
    qDebug()<<"走了 noticify dis";

    QMessageBox::Button button2 = QMessageBox::question(this,"退出","是否退回登录界面？");
    if(button2==QMessageBox::Yes){
        emit back_login_signals();
    }
    else{
        emit exit_signals();
    }
}

void MainWindow::paintEvent(QPaintEvent *e)
{
//    QPixmap pixmap = QPixmap(":/image/blue.jpg").scaled(this->size());
//    QPainter painter(this);
//    painter.drawPixmap(this->rect(),pixmap);
}

void MainWindow::init()
{
    this->setWindowTitle("主界面");
    this->setWindowIcon(QIcon(":/image/icons48.png"));
    this->setStyleSheet("#MainWindow{border-image:url(:/image/background/"+QString::number(ID_OF_BACKGROUND)+".jpg)}");

    if(msb==nullptr){//左侧工具栏
        msb = new MainSiderBar(id,this);
        msb->move(0,0);
        msb->setAutoFillBackground(true);
        connect(msb,&MainSiderBar::forwardInit, this, &MainWindow::init  );//刷新界面
        connect(msb,&MainSiderBar::back_login_signals, this, &MainWindow::back_login_slots );//退出登录
    }

    ui->searchlineEdit->setPlaceholderText("搜索");

    ui->addtoolButton->setIconSize(ui->addtoolButton->size());
    ui->addtoolButton->setIcon(QIcon(":/image/add.png"));
    ui->addtoolButton->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);");
}

void MainWindow::myConnect()
{
    chatSocket=new QTcpSocket();
    fileSocket=new QTcpSocket();
    chatSocket->connectToHost(SERVER_IP, CHAT_PORT);
    fileSocket->connectToHost(SERVER_IP, FILE_PORT);
    connect(chatSocket,&QTcpSocket::connected,this,&MainWindow::chatConnected );
    connect(fileSocket,&QTcpSocket::connected,this,&MainWindow::fileConnected  );
}

void MainWindow::showFriends()
{
    QString sql="SELECT username,state,icon,user.id FROM `user`,relationship WHERE uid1="+QString::number(id)+" AND uid2=user.id";
    refresh(sql);
}

void MainWindow::showFriends(QString sql)
{
    refresh(sql);
}

void MainWindow::refresh(QString sql)
{
    query.exec(sql);
    ui->friendsListWidget->clear();
    qDeleteAll(friends);//清空指针空间
    friends.clear();
    while(query.next()){//显示好友列表
        QString peername=query.value(0).toString();
        QString state= query.value(1).toInt() ? "在线" : "离线"  ;
        int icon=query.value(2).toInt();
        int pid = query.value(3).toInt();

        FriendWidget* f=new FriendWidget(pid,this,fileSocket,chatSocket,username,peername,state,icon,ui->friendsListWidget);
        connect(f,&FriendWidget::delete_signals,this,&MainWindow::delete_slots );

        QListWidgetItem *item=new QListWidgetItem(ui->friendsListWidget);
        item->setSizeHint(QSize(320,60));
        item->setBackground(QColor(245,245,245));

        ui->friendsListWidget->addItem(item);
        ui->friendsListWidget->setItemWidget(item,f);
        f->show();
        friends.insert(peername,f);
    }
}

void MainWindow::noticify(QString notice)
{
    QString qmsg=notice+split+username;
    QSqlQuery query(db);
    QString sql="SELECT username FROM `user`,relationship WHERE uid1="+QString::number(id)+" AND uid2=user.id  AND state=1";
    query.exec(sql);
    qmsg+=split+"notice";
    while(query.next()){
        qmsg+=split+query.value(0).toString();
    }
    if(chatSocket->isWritable())
        chatSocket->write(qmsg.toUtf8());
}

void MainWindow::chatConnected(){//通知好友自己上线
    connect(chatSocket,&QTcpSocket::readyRead,this, &MainWindow::myReceive);
    ok_chat=true;
    noticify("connected");
}

void MainWindow::fileConnected(){
    connect(fileSocket,&QTcpSocket::readyRead,this, &MainWindow::myTransfer);
    ok_file=true;
    QString qmsg="connected"+split+username;
    if(fileSocket->isWritable())
        fileSocket->write(qmsg.toUtf8());
}

void MainWindow::isConnected()
{//是否连接成功
    timer->stop();
    qDebug()<<"ok_chat="<<ok_chat;
    qDebug()<<"ok_file="<<ok_file;
    if(!ok_chat||!ok_file){QMessageBox::information(this,"","连接失败，请检查您的网络情况或重新登录");}
}

void MainWindow::myReceive()
{//接收消息
    QString qmsg="";
    while(true){
        char buffer[1024]={0};
        int len=chatSocket->read(buffer,sizeof(buffer));
        if(!len){break;}
        qmsg+=QString::fromUtf8(buffer);
    }
    QStringList qsl=qmsg.split(split);
    qDebug()<<qsl[0];
    if(qsl[0]=="notice"){
//        FriendWidget* f=friends.value(qsl[1]);
//        f->changeState();
        showFriends();//其实只要刷新表就好了
    }
    else if(qsl[0]=="msg"){
        FriendWidget* f=friends.value(qsl[1]);
        f->cc->myShow(qsl[2]);
    }
    else if(qsl[0]=="refresh"){
        showFriends();
    }

}

void MainWindow::myTransfer()
{//新建transfer专门接收文件
    QString qmsg="";
    while(true){
        char buffer[1024]={0};
        int len=fileSocket->read(buffer,sizeof(buffer));
        if(!len){break;}
        qmsg+=QString::fromUtf8(buffer);
    }
    QStringList sp = qmsg.split(split);
    int filePort=sp[0].toInt();
    qDebug()<<"emit port = "<<filePort;

    if(sp[1] == username){//发送方
        emit forwardPort(filePort);
    }
    else{//接收方
        transfer = new QTcpSocket(this);
        transfer->connectToHost(SERVER_IP,filePort);
        connect(transfer,&QTcpSocket::connected,this,[=]{qDebug()<<"接收方连接成功transfer";} );
        connect(transfer,&QTcpSocket::readyRead,this,&MainWindow::receiveFile );
    }
}

void MainWindow::receiveFile()
{
    if(fileSizeAll==0){
        QString head=transfer->readAll();

        qDebug()<<"receive  head "<<head;

        QStringList sp= head.split(split);
        fileName=sp[0];
        fileSizeAll=sp[1].toInt();
        fileSizeReceive=0;
        file.setFileName(dir+"/"+fileName);//路径
        if(file.open(QIODevice::WriteOnly|QIODevice::Append )==false){
            return;
//            QMessageBox::information(this,"","打开文件失败");
        }
    }//真实文件内容
    else{
        int len=0;
        do{
            char buffer[1024]={0};
            len=transfer->read(buffer,sizeof(buffer));
            int len2 = file.write(buffer,len);//读一点，写一点
            if(len2 >0){
                fileSizeReceive+=len2;
            }
//            int percent=(1.0*fileSizeReceive/fileSizeAll)*100;
//            qDebug()<<"fileSizeReceive = "<<fileSizeReceive;
            if(fileSizeReceive==fileSizeAll){
                QMessageBox::information(this,"","成功接收文件"+fileName+"，存放在 "+dir);
                file.close();
                fileSizeAll=0;
                delete transfer;transfer=nullptr;
                break;
            }
        }while(len>0);

    }
}

void MainWindow::search(QString text)
{
    if(text==""){//全部显示
        showFriends();
        return ;
    }
    qDebug()<<"text = "<<text;
    QString tempPeername = "%" + text + "%";
    QString sql="SELECT username,state,icon FROM "
                "(SELECT username,state,icon FROM `user`,`relationship` WHERE uid1="+QString::number(id)+" AND uid2=user.id) AS temp"
                " WHERE temp.username LIKE '"+tempPeername+"'";
    qDebug()<<"sql"<<sql;
    showFriends(sql);
}

void MainWindow::add_friend_slots()
{
    if(af==nullptr){
        af = new AddFriend(username,id);
//        af->setAttribute(Qt::WA_DeleteOnClose,true);//重载槽函数，刷新好友列表
        connect(af,&AddFriend::forwardRefresh, this, QOverload<>::of(&MainWindow::showFriends) );
        connect(af,&AddFriend::forwardNotice, this, &MainWindow::noticeRfresh);//通知添加好友
        connect(af,&AddFriend::delete_addfriend_signals, [&]{delete af;af=nullptr;});//通知添加好友
    }
    af->showMaximized();af->raise();//this->lower();
}

void MainWindow::noticeRfresh(QString pname)
{
    showFriends();
    QString qmsg="refresh"+split+username+split+pname;//通知对方刷新好友列表
    if(chatSocket->isWritable())
        chatSocket->write(qmsg.toUtf8());
}

void MainWindow::delete_slots(int pid,QString pname)
{
    int bt = QMessageBox::question(this,"删除操作确认","您是否确认删除该联系人");
    if(bt != QMessageBox::Yes)  return;
    QString sql  = "DELETE FROM `relationship` WHERE `uid1`="+QString::number(id)+" AND `uid2`="+QString::number(pid)+";";
    sql += "DELETE FROM `relationship` WHERE `uid1`="+QString::number(pid)+" AND `uid2`="+QString::number(id)+";";
    if(query.exec(sql)){
        qDebug()<<sql;
        showFriends();
        noticeRfresh(pname);
        QMessageBox::information(this,"删除成功","成功删除该联系人");
    }
}

void MainWindow::back_login_slots()
{
    if(query.exec("UPDATE `user` SET state=0 WHERE id="+QString::number(id)))
        qDebug()<<"UPDATE `user` SET state=0 WHERE id="+QString::number(id);
    if(QMessageBox::question(this,"退出","是否返回登录界面？") == QMessageBox::Yes){
        emit back_login_signals();
    }
    else{
        emit exit_signals();
    }
}
