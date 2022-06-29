#include "chat.h"
#include<QHostAddress>
#include"mysocket.h"

Chat::Chat(int port, QObject *parent)
{
    listen(QHostAddress::Any,port);
}

void Chat::incomingConnection(qintptr socketDescriptor)
{
    MySocket* socket=new MySocket();
    socket->setSocketDescriptor(socketDescriptor);//描述符
    connect(socket,&MySocket::reportMsg,this,&Chat::forwardMsg);
}

void Chat::forwardMsg(QStringList sp,MySocket* socket)
{
    if(sp[0]=="connected"){//首次连接
        qDebug()<<sp[1];
        sockets2.insert(sp[1],socket);//save socket
        int size=sp.size();
        for(int i=3;i<size;++i){//notice state
            if(!sockets2.contains(sp[i])){continue;}//no socket
            MySocket* toSocket=sockets2.value(sp[i]);
            QString qmsg="notice"+split+sp[1];
            if(toSocket->isWritable()){toSocket->write(qmsg.toUtf8());}
        }

    }
    else if(sp[0]=="msg"){
        if(!sockets2.contains(sp[2])){return;}//no socket
        MySocket* toSocket=sockets2.value(sp[2]);
        QString qmsg=sp[0]+split+sp[1]+split+sp[3];
        if(toSocket->isWritable()){toSocket->write(qmsg.toUtf8());}
    }
    else if(sp[0]=="disconnected"){
        int size=sp.size();
        for(int i=3;i<size;++i){//notice state
            if(!sockets2.contains(sp[i])){continue;}//no socket
            MySocket* toSocket=sockets2.value(sp[i]);
            QString qmsg="notice"+split+sp[1];
            if(toSocket->isWritable()){toSocket->write(qmsg.toUtf8());}
        }
        MySocket* ms= sockets2.value(sp[1]);
        ms->disconnectFromHost();
        delete ms;
        sockets2.remove(sp[1]);
    }
    else if(sp[0]=="refresh"){
        if(!sockets2.contains(sp[2])){return;}//no socket
        MySocket* toSocket=sockets2.value(sp[2]);
        QString qmsg=sp[0];
        if(toSocket->isWritable()){toSocket->write(qmsg.toUtf8());};
    }
}
