#include "mainsiderbar.h"
#include "todolist.h"
#include "ui_mainsiderbar.h"
#include<QWidget>
#include"configuration.h"

MainSiderBar::MainSiderBar(int id_, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainSiderBar),id(id_)
{
    ui->setupUi(this);

    init();

    connect(ui->icontoolButton,&QToolButton::clicked, this,  &MainSiderBar::icon_slot);//头像修改个人资料);
    connect(ui->doctoolButton_6,&QToolButton::clicked, [&]{//文本编辑界面
        if(d == nullptr)d = new doc();
        d->showMaximized();d->raise();
    } );
    connect(ui->scheduletoolButton_3,&QToolButton::clicked,[&]{//设定计划
        if(dia==nullptr)dia = new Dialog(id);
        dia->showMaximized();dia->raise();
    } );
    connect(ui->todolisttoolButton_4,&QToolButton::clicked,[&]{//待办事项
        if(to==nullptr)to = new ToDoList(id);
        to->showMaximized();to->raise();
    } );
}

MainSiderBar::~MainSiderBar()
{
    delete p;delete d;delete dia;delete to;
    delete ui;
}

void MainSiderBar::init()
{
    this->setFixedSize(QSize(55,550));//匹配主界面边栏
    this->setStyleSheet("background-color:rgb(65,138,180);");

    QWidget* blank1 = new QWidget(this);
    blank1->setFixedSize(QSize(55,25));
    blank1->move(0,55);
    QWidget* blank2 = new QWidget(this);
    blank2->setFixedSize(QSize(55,305));
    blank2->move(0,245);

    ui->icontoolButton->setIconSize(ui->icontoolButton->size());
    ui->icontoolButton->setIcon(QIcon(":/image/icon/"+QString::number(ID_OF_ICON)+".jpg"));

    ui->scheduletoolButton_3->setIconSize(QSize(25,25));
    ui->scheduletoolButton_3->setIcon(QIcon(":/image/schedule.png"));
    ui->scheduletoolButton_3->setText("设定计划");
    ui->scheduletoolButton_3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->scheduletoolButton_3->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);");

    ui->todolisttoolButton_4->setIconSize(QSize(25,25));
    ui->todolisttoolButton_4->setIcon(QIcon(":/image/todo.png"));
    ui->todolisttoolButton_4->setText("待办事项");
    ui->todolisttoolButton_4->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->todolisttoolButton_4->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);");

    ui->doctoolButton_6->setIconSize(QSize(25,25));
    ui->doctoolButton_6->setIcon(QIcon(":/image/project.png"));
    ui->doctoolButton_6->setText("项目编辑");
    ui->doctoolButton_6->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->doctoolButton_6->setStyleSheet("background-color:rgb(65,138,180);color:rgb(255,255,255);");

}

void MainSiderBar::icon_slot()
{
    if(p == nullptr){
        p = new PersonCard(id);
        connect(p,&PersonCard::forwardInit, this, &MainSiderBar::forward );
        connect(p,&PersonCard::forwardLogout, [&]{emit back_login_signals();});
        connect(p,&PersonCard::close_personcard_signals, this, [&]{delete p;p=nullptr;} );
    }
    p->showMaximized();p->raise();
}

void MainSiderBar::forward()
{
    init();
    emit forwardInit();
}
