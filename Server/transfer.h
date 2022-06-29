#ifndef TRANSFER_H
#define TRANSFER_H
#include<QTcpServer>
#include<qtcpsocket.h>
#include<QTimer>

class Transfer:public QTcpServer
{
    Q_OBJECT
public:
    Transfer(int port);
    ~Transfer();

protected://处理新的连接
    virtual void incomingConnection(qintptr socketDescriptor);

private:
    QTcpSocket* socket1=nullptr, *socket2=nullptr;
    int descrip[2];
    int index=0;
    int fileSizeAll=0;
    int fileSizeSend=0;
    QString split = "↓⊙ā";
    QTimer* timer=nullptr;

public slots:
    void send1();
    void send2();
    void myDelete();

};

#endif // TRANSFER_H
