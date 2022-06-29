#ifndef FILECLIENT_H
#define FILECLIENT_H

#include <QWidget>
#include<QTcpSocket>
#include<QFile>

namespace Ui {
class fileClient;
}

class fileClient : public QWidget
{
    Q_OBJECT

public:
    explicit fileClient(QTcpSocket* socket_, QWidget *parent = nullptr);
    ~fileClient();

protected:
    virtual void paintEvent(QPaintEvent* e);

private:
    Ui::fileClient *ui;

    QTcpSocket* socket=nullptr;
    QTcpSocket* transfer=nullptr;    
    int transferPort;

    QFile file;
    QString fileName;
    int fileSizeAll;
    int fileSizeSend;
    const QString split="↓⊙ā";//分隔

    QTimer* timer=nullptr;//先发送头信息，定时一段时间再发送本体
    QTimer* timer2=nullptr;//文件本体不要读的太快

    void init();

public slots:
    void myPort(int port);
    void mySelect();
    void mySendHead();
    void mySendFile();
    void timeSend();
signals:
    void delete_fileclient_signals();
};

#endif // FILECLIENT_H
