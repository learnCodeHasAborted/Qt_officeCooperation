#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QWidget>
#include<QTcpSocket>

namespace Ui {
class MyClient;
}

class MyClient : public QWidget
{
    Q_OBJECT

public:
    explicit MyClient(QString username_, QWidget *parent = nullptr);
    ~MyClient();

private:
    Ui::MyClient *ui;
    QTcpSocket* mySocket=nullptr;
    bool status=false;//是否连上服务器
    int port;
    QHostAddress* serverIP;
    QString username;
    bool myWrite(QString qmsg);//封装发送QString类型，返回发送结果
    bool isFirst=true;//是否第一次发送


private slots:
    void myConnect();
    void mySend();
    void myReceive();
    void myDisconnect();
    void mySuccessConnected();
};

#endif // MYCLIENT_H
