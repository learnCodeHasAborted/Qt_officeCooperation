#include "chatclient.h"
#include "configuration.h"
#include "fileclient.h"
#include "ui_chatclient.h"
#include<QDateTime>
#include"mainwindow.h"
#include<QPixmap>
#include<QPainter>
#include<QMessageBox>

chatClient::chatClient(QString _state, MainWindow* mw_, QTcpSocket* file,QTcpSocket* chat,QString username_,QString peername_,QWidget *parent) :
    QWidget(parent),ui(new Ui::chatClient),
    peername(peername_),username(username_),state(_state),chatsocket(chat),filesocket(file),mw(mw_)
{  
    ui->setupUi(this);
    init();
    ui->sendmsgpushButton_3->setFocus();//焦点
    ui->sendmsgpushButton_3->setDefault(true);
    ui->msgtextEdit->installEventFilter(this);//事件过滤器
    connect(ui->filepushButton_2,&QPushButton::clicked,this, &chatClient::newFileClient );
    connect(ui->sendmsgpushButton_3,&QPushButton::clicked,this, &chatClient::mySend );
}

chatClient::~chatClient()
{
    delete fc;
    delete ui;
}

void chatClient::closeEvent(QCloseEvent *e)
{//不关闭，只是隐藏
    e->ignore();
    if(fc)fc->hide();
    this->hide();
}

bool chatClient::eventFilter(QObject *target, QEvent *event)
{//回车键发送
    if(target == ui->msgtextEdit)
            {
                if(event->type() == QEvent::KeyPress)
                {
                     QKeyEvent *k = static_cast<QKeyEvent *>(event);
                     if(k->key() == Qt::Key_Return || k->key()==Qt::Key_Enter)
                     {
                         mySend();
                         return true;
                     }
                }
            }
    return QWidget::eventFilter(target,event);
}

void chatClient::paintEvent(QPaintEvent *e)
{
    QPixmap pixmap = QPixmap(":/image/background/"+QString::number(ID_OF_BACKGROUND)+".jpg").scaled(this->size());
    QPainter painter(this);
    painter.drawPixmap(this->rect(),pixmap);
}

void chatClient::init()
{
    setWindowTitle("聊天窗口");
    this->setWindowIcon(QIcon(":/image/icons48.png"));

    ui->peernamelabel->setText(peername);
    ui->statelabel->setText(state);

    ui->sendmsgpushButton_3->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);");
    ui->filepushButton_2->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);");
}

void chatClient::mySend()
{//发送
    QString oriMsg=ui->msgtextEdit->toPlainText();
    if(oriMsg==""){return;}
    QString qmsg="msg"+split+username+split+peername+split+oriMsg;
    std::string smsg=qmsg.toStdString();
    const char* cmsg =smsg.c_str();
    if(chatsocket->isWritable())
        chatsocket->write(cmsg);
    else{
        QMessageBox::information(this,"发送失败","与服务器连接失败，请退出后重新登录");
//        chatsocket->connectToHost(SERVER_IP,CHAT_PORT);
        return;
    }
    QDateTime curDateTime=QDateTime::currentDateTime();//当前时间
    QString space="                ";
    ui->receivetextBrowser->setTextBackgroundColor(QColor(209,217,224));//发送颜色
    ui->receivetextBrowser->append(username+space+curDateTime.toString("yyyy-MM-dd hh:mm:ss"));//消息框显示
    ui->receivetextBrowser->append(oriMsg);
    ui->msgtextEdit->clear();
}

void chatClient::transer_port_slots(int _port)
{
    emit transfer_port_signals(_port);
}

void chatClient::newFileClient()
{
    if(fc==nullptr){
        fc = new fileClient(filesocket);
    //    fc->setAttribute(Qt::WA_DeleteOnClose,true);
        QString qs="file"+split+username+split+peername;//指明传输文件双方

        if(filesocket && filesocket->isWritable())
            filesocket->write(qs.toUtf8());
        else{
            QMessageBox::warning(this,"断开连接","与服务器断开连接，请退出后重新登录");
    //        filesocket->connectToHost(SERVER_IP,FILE_PORT);
            return;
        }

        connect(fc,&fileClient::delete_fileclient_signals, [&]{delete fc;fc=nullptr;} );
        connect(mw,&MainWindow::forwardPort,fc, &fileClient::myPort);
    //    connect(mw,&MainWindow::forwardPort,this, &chatClient::transer_port_slots);
    }
    fc->showMaximized();fc->raise();
}

void chatClient::myShow(QString qmsg)
{
    QDateTime curDateTime=QDateTime::currentDateTime();//当前时间
    QString space="                ";
    ui->receivetextBrowser->setTextBackgroundColor(QColor(255,251,240));//接收颜色
    ui->receivetextBrowser->append(peername+space+curDateTime.toString("yyyy-MM-dd hh:mm:ss"));
    ui->receivetextBrowser->append(qmsg);
}

