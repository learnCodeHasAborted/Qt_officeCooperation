#ifndef MYTCPSERVICE_H
#define MYTCPSERVICE_H

#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>
#include<QMap>

namespace Ui {
class MyTCPService;
}

class MyTCPService : public QWidget
{
    Q_OBJECT

public:
    explicit MyTCPService(QWidget *parent = nullptr);
    ~MyTCPService();

private:
    Ui::MyTCPService *ui;
    QTcpServer* myServer=nullptr;
    QTcpSocket* mySocket=nullptr;
    bool ok=false;
    QMap<QString,QTcpSocket*> mySockets;
    QString toOutput(QString);

private slots:
    void myListen();
    void mySend();
    void myReceive();
    void myGetNewSocket();
    void myDisconnect();

};

#endif // MYTCPSERVICE_H
