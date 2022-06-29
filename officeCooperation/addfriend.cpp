#include "addfriend.h"
#include<QPainter>
#include "configuration.h"
#include "ui_addfriend.h"
#include"friendwidget.h"
#include<QMessageBox>

AddFriend::AddFriend(QString uname, int id_, QWidget *parent) :
    QWidget(parent),ui(new Ui::AddFriend),
    id(id_),username(uname)
{
    ui->setupUi(this);
    ui->lineEdit->setFocus();
    this->setWindowTitle("添加好友");
    this->setWindowIcon(QIcon(":/image/icons48.png"));
    ui->pushButton->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);border-radius:5px;");
    ui->pushButton->setShortcut(Qt::Key_Enter);
    ui->pushButton->setShortcut(Qt::Key_Return);
    md=new MyDatabase("add"+uname);//数据库初始化
    db=md->getDatabase();
    query=QSqlQuery(db);
    connect(ui->pushButton,&QPushButton::clicked,this, &AddFriend::showFriends  );
}

AddFriend::~AddFriend()
{
    emit forwardRefresh();//通知刷新好友列表
    delete ui;
}

void AddFriend::paintEvent(QPaintEvent *e)
{
    QPixmap pixmap = QPixmap(":/image/background/"+QString::number(ID_OF_BACKGROUND)+".jpg").scaled(this->size());
    QPainter painter(this);
    painter.drawPixmap(this->rect(),pixmap);
}

void AddFriend::closeEvent(QCloseEvent *e)
{
    emit delete_addfriend_signals();
}

void AddFriend::showFriends()
{
    if(ui->lineEdit->text()==""){QMessageBox::information(this,"","请输入您想查询的联系人关键词");return;}
    QString peername = "%" + ui->lineEdit->text() + "%";
    QString sql="SELECT id,username,state,icon FROM `user` WHERE username like '"+peername+"'";

    query.exec(sql);

    ui->friendsListWidget->clear();
    qDeleteAll(friends);//清空指针空间
    friends.clear();

    while(query.next()){//显示好友列表
        int peerid = query.value(0).toInt();
        QString peername=query.value(1).toString();
        QString state= query.value(2).toInt() ? "在线" : "离线"  ;
        int icon=query.value(3).toInt();

        FriendWidget* f=new FriendWidget(peerid,peername,state,icon,ui->friendsListWidget);
        QListWidgetItem *item=new QListWidgetItem(ui->friendsListWidget);
        item->setSizeHint(QSize(320,60));
        ui->friendsListWidget->addItem(item);
        ui->friendsListWidget->setItemWidget(item,f);
        f->show();
        friends.push(f);
        connect(f,&FriendWidget::forwardPeer,this,&AddFriend::add  );
    }
}

void AddFriend::add(int peerid ,QString peername)
{
    int res = QMessageBox::information(this,"","是否添加对方为好友？",QMessageBox::Yes,QMessageBox::No );
    if(res == QMessageBox::Yes ){
        if(peername==username){QMessageBox::information(this,"","您不能将自己添加为联系人");return;}
        QString sql = "SELECT uid1 FROM relationship WHERE uid1="+QString::number(id)+" AND uid2="+QString::number(peerid);
        query.exec(sql);
        if(query.next()){//是否已经是好友了
            QMessageBox::information(this,"","您已添加对方为好友，请勿重复添加");
            return ;
        }
        else{
            QString sql = "INSERT INTO `relationship` (uid1,uid2) VALUES('"+QString::number(id)+"','"+QString::number(peerid)+"')";
            bool ok1 = query.exec(sql);
            sql = "INSERT INTO `relationship` (uid2,uid1) VALUES('"+QString::number(id)+"','"+QString::number(peerid)+"')";
            bool ok2 = query.exec(sql);
            if(!ok1||!ok2){QMessageBox::information(this,"","添加好友失败，请重新尝试");}
            else{
                emit forwardNotice(peername);
                QMessageBox::information(this,"","添加好友成功");
            }
        }
    }
}
