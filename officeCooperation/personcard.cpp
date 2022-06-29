#include "personcard.h"
#include "ui_personcard.h"
#include<QWidget>
#include<QListWidget>
#include"configuration.h"
#include<QLabel>
#include<QToolButton>
#include"picture.h"
#include<QMessageBox>
#include<QLineEdit>
#include"passwordreset.h"

PersonCard::PersonCard(int i,QWidget *parent) :
    QWidget(parent),ui(new Ui::PersonCard),
    id(i)
{
    ui->setupUi(this);
    init();
    md=new MyDatabase("personcard"+QString::number(id));//数据库初始化
    db=md->getDatabase();
    query=QSqlQuery(db);
    connect(ui->icontoolButton, &QToolButton::clicked,this, &PersonCard::showIcon );
    connect(ui->backgroundtoolButton_2, &QToolButton::clicked,this, &PersonCard::showBackground );
    connect(ui->passwordtoolButton_5, &QToolButton::clicked,this, &PersonCard::setPassword );
    connect(ui->exittoolButton_3, &QToolButton::clicked,this, &PersonCard::logout );
}

PersonCard::~PersonCard()
{
    qDebug()<<"Personcard 析构";
    delete md;delete iw;delete bw;delete pw;delete pixmap;delete pixmap2;
    delete ui;
}

void PersonCard::closeEvent(QCloseEvent *e)
{
    emit close_personcard_signals();//通知工具窗口析构personcard
}

void PersonCard::init()
{
    this->setWindowTitle("个人名片");
    this->setWindowIcon(QIcon(":/image/icons48.png"));

    if(pixmap==nullptr) pixmap = new QPixmap();
    pixmap->load(":/image/icon/"+QString::number(ID_OF_ICON)+".jpg");
    pixmap->scaled(ui->iconlabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->iconlabel->setScaledContents(true);
    ui->iconlabel->setPixmap(*pixmap);

    if(pixmap2==nullptr) pixmap2 = new QPixmap();
    pixmap2->load(":/image/background/"+QString::number(ID_OF_BACKGROUND)+".jpg");
    pixmap2->scaled(ui->iconlabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->backgroundlabel->setScaledContents(true);
    ui->backgroundlabel->setPixmap(*pixmap2);

    ui->icontoolButton->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);");
    ui->backgroundtoolButton_2->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);");
    ui->passwordtoolButton_5->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);");
    ui->exittoolButton_3->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);");
}

void PersonCard::showIcon()
{
    if(iw==nullptr) {
        iw = new QWidget();
        iw->setWindowTitle("选择头像");
        iw->setWindowIcon(QIcon(":/image/icons48.png"));
        iw->setFixedSize(QSize(400,400));

        for(int i=0;i<NUMBER_OF_ICONS;i++){
            int x = 0+100*(i%4);int y = 0+100*(i/4);
            Picture* pic = new Picture("icon",i+1,iw);
            pic->move(x,y);
            connect(pic,&Picture::forwardPicture,this, &PersonCard::setIcon );
        }
    }
    iw->showMaximized();iw->raise();
    if(bw)bw->close();if(pw)pw->close();
}

void PersonCard::setIcon(int i)
{
    QMessageBox::Button button = QMessageBox::question(iw,"选择头像","是否设置选中图片为头像？");
    if(button == QMessageBox::Yes){
        ID_OF_ICON = i;
        init();
        QString sql = "UPDATE `user` SET icon="+QString::number(ID_OF_ICON)+" WHERE `id`="+QString::number(id);
        query.exec(sql);
        emit forwardInit();
    }
}

void PersonCard::showBackground()
{
    if(bw==nullptr) {
        bw = new QWidget();
        bw->setWindowTitle("选择背景");
        bw->setWindowIcon(QIcon(":/image/icons48.png"));
        bw->setFixedSize(QSize(400,400));

        for(int i=0;i<NUMBER_OF_BACKGROUNDS;i++){
            int x = 0+200*(i%2);int y = 0+100*(i/2);
            Picture* pic = new Picture("background",i+1,bw);
            pic->move(x,y);
            connect(pic,&Picture::forwardPicture,this, &PersonCard::setBackground );
        }
    }
    bw->showMaximized();bw->raise();
    if(iw)iw->close();if(pw)pw->close();
}

void PersonCard::setBackground(int i)
{
    QMessageBox::Button button = QMessageBox::question(bw,"选择背景","是否设置选中图片为背景？");
    if(button == QMessageBox::Yes){
        ID_OF_BACKGROUND = i;
        init();
        QString sql = "UPDATE `user` SET background="+QString::number(ID_OF_BACKGROUND)+" WHERE `id`="+QString::number(id);
        query.exec(sql);
        emit forwardInit();
    }
}

void PersonCard::setPassword()
{
    if(pw==nullptr) pw = new PasswordReset(id);
    pw->showMaximized();pw->raise();
    if(iw)iw->close();if(bw)bw->close();
}

void PersonCard::logout()
{
    emit forwardLogout();
}
