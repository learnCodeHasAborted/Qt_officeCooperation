#include "mytcpservice.h"
#include "ui_mytcpservice.h"
#include<QHostAddress>
#include<QMessageBox>

#include<QDebug>
using namespace std;


MyTCPService::MyTCPService(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyTCPService)
{
    ui->setupUi(this);
    ui->portLine->setText("23333");
    ui->listenBtn->setShortcut(Qt::Key_Enter);
    ui->listenBtn->setShortcut(Qt::Key_Return);
}

MyTCPService::~MyTCPService()
{
    delete ui;
}

QString MyTCPService::toOutput(QString all)
{
    QStringList sl=all.split("|");
    if(sl[0]=="connected"){
        QString curUsername=sl[1];
        QString msg=sl[2];

    }
    else if(sl[0]=="msg"){
        QString curUsername=sl[1];
        QString msg=sl[2];
    }
    else if(sl[0]=="disconnected"){
        QString curUsername=sl[1];
        QString msg=sl[2];
    }
    return sl[2];
}

void MyTCPService::myListen()
{
    if(myServer==nullptr){
        myServer=new QTcpServer();
    }
    int port=ui->portLine->text().toInt();
//
    if(!myServer->listen(QHostAddress::Any,port)){
        QMessageBox::critical(this,"监听失败","服务器监听失败,请您检查端口设置或网络连接情况");
        return;
    }
    else{
        ok=true;
        ui->listenBtn->setEnabled(false);
        connect(myServer,SIGNAL(newConnection()),this,SLOT(myGetNewSocket()));//新连接
        QKeySequence key1(Qt::CTRL+Qt::Key_Enter);
        QKeySequence key2(Qt::CTRL+Qt::Key_Return);
        ui->sendBtn->setShortcut(key1);
        ui->sendBtn->setShortcut(key2);
        QMessageBox::information(this,"监听成功","服务器监听成功,可以开始接收、发送消息");
    }
}

void MyTCPService::mySend()
{
    qDebug()<<"mysend";
    if(!mySocket->isValid()){
        QMessageBox::information(this,"发送失败","socket不合法");
        qDebug()<<"发送失败socket不合法\n";
        return ;
    }
    QString qmsg=ui->sendTextEdit->toPlainText();
    ui->receiveTextBrowser->append(qmsg);

    if(qmsg==""){
        QMessageBox::information(this,"发送失败","发送信息为空，请输入信息后再发送");
        qDebug()<<"发送信息为空，请输入信息后再发送\n";
        return ;
    }

    ui->sendTextEdit->clear();

    string smsg=qmsg.toStdString();
    const char* chmsg=smsg.c_str();
    qDebug()<<"chmsg"<<chmsg;
    int res=mySocket->write(chmsg,strlen(chmsg));
    if(res==-1){
        qDebug()<<"socket发送失败\n";
        QMessageBox::information(this,"发送失败","socket发送失败");
    }
}

void MyTCPService::myReceive()
{
    char buffer[1024]={0};
    mySocket=mySockets.first();
    int numRead=mySocket->read(buffer,1024);
//    if(numRead==0){
//        QMessageBox::critical(this,"接收失败","未接收到对方发送的消息");
//        return ;
//    }
    QString all=QString::fromUtf8(buffer,strlen(buffer));
    while(numRead){
        numRead=mySocket->read(buffer,1024);
        all+=QString::fromUtf8(buffer,strlen(buffer));
    }
    //字符串处理
    QString output=toOutput(all);
    ui->receiveTextBrowser->append(all);
}

void MyTCPService::myGetNewSocket()
{
    QTcpSocket* newSocket = new QTcpSocket(this);
    newSocket= myServer->nextPendingConnection();
    mySockets.insert("a",newSocket);
    connect(newSocket,SIGNAL(readyRead()),this,SLOT(myReceive()));
//    mySocket=myServer->nextPendingConnection();
//    if(!mySocket){
//        QMessageBox::critical(this,"连接失败","获取客户端连接失败");
//        return ;
//    }
//    else{
//        QMessageBox::information(this,"连接成功","获取客户端连接成功");
//        connect(mySocket,SIGNAL(readyRead()),this,SLOT(myReceive()));
//        connect(mySocket,SIGNAL(disconnected()),this,SLOT(myDisconnect()));
//    }
}

void MyTCPService::myDisconnect()
{
    QMessageBox::information(this,"连接断开","与对方连接断开");
}


