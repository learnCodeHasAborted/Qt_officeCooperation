#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QWidget>
#include "friendwidget.h"
#include"mydatabase.h"
#include<QStack>

namespace Ui {
class AddFriend;
}

class AddFriend : public QWidget
{
    Q_OBJECT

public:
    explicit AddFriend(QString uname,int id,QWidget *parent = nullptr);
    ~AddFriend();
protected:
    virtual void paintEvent(QPaintEvent* e);
    virtual void closeEvent(QCloseEvent* e);
private:
    Ui::AddFriend *ui;
    int id;
    MyDatabase* md=nullptr;
    QSqlDatabase db;
    QSqlQuery query;
    QString username;
    QStack<FriendWidget*> friends;
public slots:
    void showFriends();
    void add(int peerid, QString peername);

signals:
    void forwardRefresh();
    void forwardNotice(QString peername);
    void delete_addfriend_signals();
};

#endif // ADDFRIEND_H
