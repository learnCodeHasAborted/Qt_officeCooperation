#include "myclient.h"
#include "ui_myclient.h"
#include<QMessageBox>
#include<QHostAddress>
#include <synchapi.h>
using namespace std;

MyClient::MyClient(QString username_,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyClient),username(username_)
{
    ui->setupUi(this);

    serverIP=new QHostAddress();
    port = 23333;
    //未连接不能发送消息
    ui-> sendpushButton->setEnabled(false);

    ui->iplineEdit->setText("127.0.0.1");
    ui->portlineEdit->setText("23333");
    ui->connectpushButton->setShortcut(Qt::Key_Enter);
    ui->connectpushButton->setShortcut(Qt::Key_Return);
    connect(ui->connectpushButton,SIGNAL(clicked()),this,SLOT(myConnect()));//绑定连接
    connect(ui->sendpushButton,SIGNAL(clicked()),this,SLOT(mySend()));
}

MyClient::~MyClient()
{
    delete ui;
}

bool MyClient::myWrite(QString qmsg)
{
    string smsg=qmsg.toStdString();
    const char* chmsg=smsg.c_str();
    int res=mySocket->write(chmsg,strlen(chmsg));
    return res==-1 ? false : true;
}

void MyClient::myConnect()
{//已经连接，此时点击按钮断开连接
    if(status){
        //发送下线消息
        QString qmsg="disconnected|"+username;
        myWrite(qmsg);
        mySocket->disconnectFromHost();
        status=false;
    }
    else{
        QString ip = ui->iplineEdit->text();//ip isvalid
        if(!serverIP->setAddress(ip)){
            QMessageBox::critical(this,"连接失败","ip地址不合法");
            return ;
        }
        if(!mySocket){
            mySocket=new QTcpSocket(this);//绑定parent应该可以自动析构
        }
        int port=ui->portlineEdit->text().toInt();
        mySocket->connectToHost(*serverIP,port);
        if(!mySocket->waitForConnected(5000)){//5秒超时失败
            QMessageBox::information(this,"连接失败","响应超时，连接失败，请检查您的网络连接");
            return ;
        }
        else{
            status=true;

            //发送键激活，并绑定快捷键ctrl+enter
            ui->sendpushButton->setEnabled(true);
            QKeySequence key1(Qt::CTRL+Qt::Key_Enter);
            QKeySequence key2(Qt::CTRL+Qt::Key_Return);
            ui->sendpushButton->setShortcut(key1);
            ui->sendpushButton->setShortcut(key2);
            //连接按钮显示为断开按钮
            ui->connectpushButton->setText("断开");
            connect(mySocket,&QTcpSocket::connected, this, &MyClient::mySuccessConnected);

            connect(mySocket,SIGNAL(readyRead()),this,SLOT(myReceive()));
            connect(mySocket,SIGNAL(disconnected()),this,SLOT(myDisconnect()));
            QMessageBox::information(this,"连接成功","连接成功,可以开始接收、发送消息");
        }
    }

}

void MyClient::mySend()
{
    qDebug()<<"client mysend";
    if(!mySocket->isValid()){
        QMessageBox::information(this,"发送失败","socket不合法");
        qDebug()<<"发送失败socket不合法\n";
        return ;
    }

    QString qmsg=ui->sendtextEdit->toPlainText();

    if(qmsg==""){
        QMessageBox::information(this,"发送失败","发送信息为空，请输入信息后再发送");
        qDebug()<<"发送信息为空，请输入信息后再发送\n";
        return ;
    }

    ui->sendtextEdit->clear();
    ui->receivetextBrowser->append(username+":\n"+qmsg);
    bool res=false;
    if(isFirst){
        isFirst=false;
        //向服务器注册连接信息
        qmsg="connected|"+username+"|"+qmsg;
        res=myWrite(qmsg);
    }
    else{
        res=myWrite("msg|"+username+"|"+qmsg);
    }
    if(!res){
        qDebug()<<"socket发送失败\n";
        QMessageBox::information(this,"发送失败","socket发送失败");
    }
}

void MyClient::myReceive()
{
    char buffer[1024]={0};
    int numRead=mySocket->read(buffer,1024);
    while(numRead){
        ui->receivetextBrowser->append(QString::fromUtf8(buffer,strlen(buffer)));
        numRead=mySocket->read(buffer,1024);
    }
}

void MyClient::myDisconnect()
{
    ui->connectpushButton->setText("连接");
    ui->sendpushButton->setEnabled(false);
    QMessageBox::information(this,"连接断开","与对方连接断开");
}

void MyClient::mySuccessConnected()
{
    myWrite(QString("连接成功|"+username));
}
