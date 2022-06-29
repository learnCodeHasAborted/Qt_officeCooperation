#ifndef CHAT_H
#define CHAT_H
#include<QTcpServer>
#include<QMap>
#include"mysocket.h"
#include<QStringList>

class Chat:public QTcpServer
{
    Q_OBJECT
public:
    explicit Chat(int port,QObject *parent=nullptr);
    QMap<QString,MySocket*> sockets2;//username，socket
protected://处理新的连接
    virtual void incomingConnection(qintptr socketDescriptor);

public slots:
    void forwardMsg(QStringList,MySocket*);
private:
    const QString split="↓⊙ā";
};

#endif // CHAT_H
