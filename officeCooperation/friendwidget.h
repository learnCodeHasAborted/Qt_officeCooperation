#ifndef FRIENDWIDGET_H
#define FRIENDWIDGET_H

#include <QWidget>
#include<QTcpSocket>
#include<QLabel>
#include<QPushButton>
#include"chatclient.h"
#include<QAction>

class MainWindow;

namespace Ui {
class FriendWidget;
}

class FriendWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FriendWidget(int peerid,MainWindow* mw, QTcpSocket* file,QTcpSocket* chat,QString username,QString peername,QString state,int icon_,QWidget *parent = nullptr);
    explicit FriendWidget(int peerid,QString peername,QString state,int icon_,QWidget *parent = nullptr);
    ~FriendWidget();

    void setPeername(const QString &newPeername);

    void changeState();

    chatClient* cc=nullptr;

protected:
    virtual void mousePressEvent(QMouseEvent *event);//鼠标点击
    virtual void contextMenuEvent(QContextMenuEvent *event);//右键菜单
private:
    Ui::FriendWidget *ui;
    int peerid;
    QString username;
    QString peername;
    QString state;//在线状态
    int icon;//头像
    QTcpSocket* chatSocket=nullptr;
    QTcpSocket* fileSocket=nullptr;
    bool isOverload=false;//是否重载，已有的联系人和搜索出来的不一样

    QAction* act_delete = nullptr;

    void init();
public slots:
    void delete_slots();
signals:
    void forwardPeer(int peerid, QString peername);
    void delete_signals(int peerid,QString peername);
};

#endif // FRIENDWIDGET_H
