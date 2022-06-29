#include "friendwidget.h"
#include "ui_friendwidget.h"
#include<QPixmap>
#include"chatclient.h"
#include<QMessageBox>
#include<QPixmap>
#include<QWidget>
#include<QMenu>
#include<QCursor>

FriendWidget::FriendWidget(int peerid_, MainWindow* mw, QTcpSocket* file, QTcpSocket* chat, QString username_, QString peername_, QString state_, int icon_, QWidget *parent) :
    QWidget(parent),ui(new Ui::FriendWidget),peerid(peerid_),username(username_),peername(peername_),
    state(state_),icon(icon_),chatSocket(chat),fileSocket(file)
{
    ui->setupUi(this);
    //初始化界面
    init();
    act_delete = new QAction("删除联系人",this);
    connect(act_delete,&QAction::triggered, this, &FriendWidget::delete_slots );
    cc=new chatClient(state, mw, fileSocket,chatSocket,username,peername);//聊天框
    cc->setAutoFillBackground(true);
}

FriendWidget::FriendWidget(int peerid_, QString peername_, QString state_, int icon_, QWidget *parent):
    QWidget(parent),ui(new Ui::FriendWidget),peerid(peerid_),peername(peername_),state(state_),
    icon(icon_)
{
    ui->setupUi(this);
    isOverload = true;
    init();
}


FriendWidget::~FriendWidget()
{
    if(!isOverload)
        delete cc;
    delete ui;
}

void FriendWidget::changeState()
{
    if(state=="在线"){
        state="离线";
    }
    else if(state=="离线"){
        state="在线";
    }
    ui->statelabel_3->setText(state);
}

void FriendWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton){
        QCursor cur  = this->cursor();
        QMenu* menu =  new QMenu(this);
        menu->addAction(act_delete);
        menu->exec(cur.pos());
    }
    else{
        if(!isOverload){cc->showMaximized();cc->raise();}
        else
            emit forwardPeer(peerid,peername);
    }
}

void FriendWidget::contextMenuEvent(QContextMenuEvent *event)
{
//    QCursor cur  = this->cursor();
//    QMenu* menu =  new QMenu(this);
//    menu->addAction(act_delete);
//    menu->exec(cur.pos());
}

void FriendWidget::init()
{
    QPixmap *pixmap = new QPixmap(":/image/icon/"+QString::number(icon)+".jpg");
    pixmap->scaled(ui->iconlabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->iconlabel->setScaledContents(true);
    ui->iconlabel->setPixmap(*pixmap);

    ui->peernamelabel_2->setText(peername);
    ui->statelabel_3->setText(state);
}

void FriendWidget::delete_slots()
{
    emit delete_signals(peerid,peername);
}

