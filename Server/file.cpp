#include "file.h"
#include<QHostAddress>
#include"mysocket.h"
#include"transfer.h"

File::File(int port, QObject *parent)
{
    listen(QHostAddress::Any,port);
}

void File::incomingConnection(qintptr socketDescriptor)
{
    MySocket* socket=new MySocket();
    socket->setSocketDescriptor(socketDescriptor);//描述符
    connect(socket,&MySocket::reportMsg,this,&File::forwardMsg);
}

void File::forwardMsg(QStringList sp,MySocket* socket)
{
    if(sp[0]=="connected"){//首次连接
        sockets2.insert(sp[1],socket);//save socket
    }
    else if(sp[0]=="file"){
        if(!sockets2.contains(sp[2])){return;}//no socket
        MySocket* toSocket=sockets2.value(sp[2]);
        int curPort=port++;
        if(port==20000){port=10000;}
        Transfer* mt = new Transfer(curPort);
        QString qmsg = QString::number(curPort)+split+sp[1]+split+sp[2];
        if(socket->isWritable()){socket->write(qmsg.toUtf8());}
        if(toSocket->isWritable()){toSocket->write(qmsg.toUtf8());}
    }
    else if(sp[0]=="disconnected"){
        MySocket* ms= sockets2.value(sp[1]);
        ms->disconnectFromHost();
        delete ms;
        sockets2.remove(sp[1]);
    }
}
