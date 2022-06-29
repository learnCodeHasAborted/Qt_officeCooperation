#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addfriend.h"
#include "friendwidget.h"
#include "mainsiderbar.h"
#include"mydatabase.h"
#include<QMap>
#include<QCloseEvent>
#include<QTcpSocket>
#include<QTimer>

#include<QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int id_,QString uername_, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void closeEvent(QCloseEvent* e);
    virtual void paintEvent(QPaintEvent* e);

private:
    Ui::MainWindow *ui;
    void init();
    MyDatabase* md=nullptr;
    QSqlDatabase db;
    QSqlQuery query;
    int id;
    QString username;
    QMap<QString,FriendWidget*> friends;
    void myConnect();
    QTcpSocket* chatSocket=nullptr;
    QTcpSocket* fileSocket=nullptr;
    bool ok_chat=false,ok_file=false;//连接是否成功
    QTimer* timer=nullptr;//延时判断
    const QString split="↓⊙ā";
    void showFriends();
    void showFriends(QString sql);
    void refresh(QString sql);
    QTcpSocket* transfer=nullptr;
    void noticify(QString);
    MainSiderBar* msb=nullptr;
    AddFriend* af=nullptr;

public slots:
    void chatConnected();
    void fileConnected();
    void isConnected();
    void myReceive();
    void myTransfer();
    void receiveFile();
    void search(QString text);
    void add_friend_slots();
    void noticeRfresh(QString pname);
    void delete_slots(int pid,QString pname);
    void back_login_slots();



//传文件
private:
    QFile file;
    QString fileName="";
    int fileSizeAll=0;
    int fileSizeReceive=0;
    QString dir="C:/officeCooperation/download"; //接收文件所在目录C:\officeCooperation\download

signals:
    void forwardMsg(QString);
    void forwardPort(int);
    void back_login_signals();
    void exit_signals();
};

#endif // MAINWINDOW_H
