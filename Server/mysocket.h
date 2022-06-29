#ifndef MYSOCKET_H
#define MYSOCKET_H
#include<QTcpSocket>
#include<QStringList>

class MySocket:public QTcpSocket
{
    Q_OBJECT
public:
    explicit MySocket();
    const QString split="↓⊙ā";

private:
    QString username="";//一个socket绑定 一个user

signals:
    void reportMsg(QStringList,MySocket*);//消息给服务器转发

public slots:
    void myReceive();//处理接收消息
};

#endif // MYSOCKET_H
