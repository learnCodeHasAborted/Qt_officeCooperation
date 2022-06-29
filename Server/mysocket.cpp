#include "mysocket.h"

MySocket::MySocket()
{
    connect(this,&MySocket::readyRead,this,&MySocket::myReceive);
}

void MySocket::myReceive()
{
    QString qmsg="";
    while(true){
        char buffer[1024]={0};
        int len=this->read(buffer,sizeof(buffer));
        if(!len){break;}
        qmsg+=QString::fromUtf8(buffer);
    }
    QStringList sp=qmsg.split(split);
    if(username=="")username=sp[1];
    emit reportMsg(sp,this);
}
