#ifndef FILE_H
#define FILE_H
#include<QTcpServer>
#include<QMap>
#include"mysocket.h"
#include<QStringList>

class File:public QTcpServer
{
    Q_OBJECT
public:
    explicit File(int port,QObject *parent=nullptr);
    QMap<QString,MySocket*> sockets2;//username，socket
protected://处理新的连接
    virtual void incomingConnection(qintptr socketDescriptor);

public slots:
    void forwardMsg(QStringList,MySocket*);
private:
    const QString split="↓⊙ā";
    int port=10000;//true transfer file port , auto_increment
};

#endif // FILE_H
