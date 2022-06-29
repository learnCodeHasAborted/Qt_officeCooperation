#include "fileclient.h"
#include "ui_fileclient.h"
#include<QTimer>
#include<QMessageBox>
#include<QFileDialog>
#include<QPainter>
#include"configuration.h"

fileClient::fileClient(QTcpSocket* socket_,QWidget *parent) :
    QWidget(parent),ui(new Ui::fileClient),
    socket(socket_)
{
    ui->setupUi(this);
    init();

    timer=new QTimer(this);

    connect(ui->selectpushButton,&QPushButton::clicked,this,&fileClient::mySelect );
    connect(timer,&QTimer::timeout,this, &fileClient::mySendFile );//定时到，发送文件本体
    connect(ui->sendpushButton,&QPushButton::clicked,this, &fileClient::mySendHead);//发送，先发送头信息
}

fileClient::~fileClient()
{
    qDebug()<<"走了fileclient 析构";
    delete ui;
}

void fileClient::paintEvent(QPaintEvent *e)
{
    QPixmap pixmap = QPixmap(":/image/background/"+QString::number(ID_OF_BACKGROUND)+".jpg").scaled(this->size());
    QPainter painter(this);
    painter.drawPixmap(this->rect(),pixmap);
}

void fileClient::init()
{
    setWindowTitle("文件传输");
    this->setWindowIcon(QIcon(":/image/icons48.png"));
    ui->progressBar->setVisible(false);//先不显示进度条
    ui->filelineEdit->setText("");
    ui->sendpushButton->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);");
    ui->selectpushButton->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);");
}

void fileClient::myPort(int port)
{//确定好传输对象以后，新建transfer专门传文件
    qDebug()<<"发送创建 trannsefer "<<port;
    transferPort= port;
    transfer = new QTcpSocket(this);
    transfer->connectToHost(SERVER_IP,port);
    connect(transfer,&QTcpSocket::connected,this,[=]{qDebug()<<"发送方连接成功";});
}

void fileClient::mySelect()
{
    QString path=QFileDialog::getOpenFileName(this);
    ui->filelineEdit->setText(path);
}

void fileClient::mySendHead()
{//文件名，文件大小，已发送大小
    QString path=ui->filelineEdit->text();
    if(path==""){
        QMessageBox::information(this,"发送失败","请先选择需要发送的文件");
        return;
    }
    if(transfer==nullptr){
        QMessageBox::information(this,"发送失败","发送失败，请重新发送");
        emit delete_fileclient_signals();
        return;
    }
    file.setFileName(path);//文件
    QFileInfo info(path);
    fileName=info.fileName();
    fileSizeAll=info.size();
    fileSizeSend=0;
    QString head=fileName+split+QString::number(fileSizeAll) ;

    qDebug()<<"head filename and size"<<head;
    int len = 0;
    if(transfer->isWritable())
        len=transfer->write(head.toUtf8());
    else{
        QMessageBox::information(this,"发送失败","发送失败，请重新发送");
        emit delete_fileclient_signals();
        return;
    }
    if(len){
        ui->filelineEdit->setEnabled(false);
        ui->selectpushButton->setEnabled(false);
        ui->sendpushButton->setDisabled(true);
        timer->start(50);
    }//延时发送本体
    else{QMessageBox::information(this,"发送失败","文件信息发送失败，请重新发送");emit delete_fileclient_signals();}
}

void fileClient::mySendFile()
{
    timer->stop();//停止定时器
    if(file.open(QIODevice::ReadOnly )==false){
        QMessageBox::information(this,"发送失败","打开文件失败，请重新发送");
        return;
    }
    ui->progressBar->setVisible(true);
    timer2 = new QTimer(this);
    connect(timer2,&QTimer::timeout, this, &fileClient::timeSend );
    timer2->start(1);
}

void fileClient::timeSend()
{
    char buffer[4096]={0};
    int len=file.read(buffer,sizeof(buffer));
    if(transfer && transfer->isWritable()){
        int len2 = transfer->write(buffer,len);
        fileSizeSend+=len2;
        ui->progressBar->setValue(1.0*fileSizeSend/fileSizeAll*100);
        if(fileSizeSend==fileSizeAll){
            timer2->stop();
            file.close();
            QMessageBox::information(this,"发送成功","文件发送成功");
            emit delete_fileclient_signals();
        }
    }
    else{
        QMessageBox::information(this,"发送失败","发送失败，请重新连接服务器");
        emit delete_fileclient_signals();
    }
}
