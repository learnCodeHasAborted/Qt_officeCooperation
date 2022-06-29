#include "transfer.h"
#include<QTimer>

Transfer::Transfer(int port)
{
    listen(QHostAddress::Any, port);
}

Transfer::~Transfer()
{
    qDebug()<<"delete transfer ";

    delete timer;
}

void Transfer::incomingConnection(qintptr socketDescriptor)
{
    if(socket1==nullptr){
        socket1 = new QTcpSocket(this);
        socket1->setSocketDescriptor(socketDescriptor);
        connect(socket1,&QTcpSocket::readyRead,this, &Transfer::send1 );
    }
    else{
        socket2 = new QTcpSocket(this );
        socket2->setSocketDescriptor(socketDescriptor);
        connect(socket2,&QTcpSocket::readyRead,this, &Transfer::send2 );
    }
}

void Transfer::myDelete()
{
    timer->stop();
    delete this;
}

void Transfer::send1(){
    if(fileSizeAll == 0){
       QString head = socket1->readAll();
       QStringList sp = head.split(split);
       fileSizeAll = sp[1].toInt();
       fileSizeSend = 0;
       if(socket2->isWritable()){socket2->write(head.toUtf8());}
    }
    else{
        int len= 0;
        do{
            char buffer[1024]={0};
            len = socket1->read(buffer ,sizeof(buffer));
            if(socket2->isWritable()){socket2->write(buffer,len);}
            if(len>0){fileSizeSend += len;}
            if(fileSizeAll == fileSizeSend){
                timer = new QTimer(this);
                timer->start(10000);
                connect(timer, &QTimer::timeout, this,&Transfer::myDelete  );
            }
        }while(len>0);
    }
}

void Transfer::send2()
{
    if(fileSizeAll == 0){
       QString head = socket2->readAll();
       QStringList sp = head.split(split);
       fileSizeAll = sp[1].toInt();
       fileSizeSend = 0;
       if(socket1->isWritable()){socket1->write(head.toUtf8());}
    }
    else{
        int len= 0;
        do{
            char buffer[1024]={0};
            len = socket2->read(buffer ,sizeof(buffer));
            if(socket1->isWritable()){socket1->write(buffer,len);}
            if(len>0){fileSizeSend += len;}
            if(fileSizeAll == fileSizeSend){
                timer = new QTimer(this);
                timer->start(10000);
                connect(timer, &QTimer::timeout, this,&Transfer::myDelete  );
            }
        }while(len>0);
    }
}
