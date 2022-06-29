#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include "fileclient.h"
#include <QWidget>
#include<QTcpSocket>
#include<QCloseEvent>

class MainWindow;

namespace Ui {
class chatClient;
}

class chatClient : public QWidget
{
    Q_OBJECT

public:
    explicit chatClient(QString _state, MainWindow* mw_, QTcpSocket* file, QTcpSocket* chat, QString username_, QString peername_, QWidget *parent = nullptr);
    ~chatClient();
    void myShow(QString);//显示转发过来的消息

protected:
    virtual void closeEvent(QCloseEvent* e);
    bool eventFilter(QObject *target, QEvent *e);//事件过滤器，回车键发送消息
    virtual void paintEvent(QPaintEvent* e);

private:
    Ui::chatClient *ui;

    QString peername;
    QString username;
    QString state;

    const QString split="↓⊙ā";
    QTcpSocket* chatsocket=nullptr;
    QTcpSocket* filesocket=nullptr;

    fileClient *fc=nullptr;

    MainWindow* mw=nullptr;

    void init();

public slots:
    void mySend();
    void transer_port_slots(int _port);
    void newFileClient();

signals:
    void transfer_port_signals(int _port);
};

#endif // CHATCLIENT_H
