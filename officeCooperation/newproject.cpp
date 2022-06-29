#include "newproject.h"
#include "ui_newproject.h"

#include <QFileDialog>
#include <QMessageBox>

NewProject::NewProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProject)
{
    ui->setupUi(this);
    setWindowTitle("项目");
    this->setWindowIcon(QIcon(":/image/icons48.png"));
    //选择新建项目目录按钮信号槽
    connect(ui->chooseProjectDir,SIGNAL(clicked()),this,SLOT(choose_project_dir()));
    //确定按钮信号槽
    connect(ui->okNewProject,SIGNAL(clicked()),this,SLOT(ok_new_project()));
    //取消按钮信号槽
    connect(ui->cancelNewProject,SIGNAL(clicked()),this,SLOT(cancel_new_project_()));
    //连接接受槽
    connect(ui->okNewProject,SIGNAL(clicked()),this,SLOT(accept()));
    //连接拒绝槽
    connect(ui->cancelNewProject,SIGNAL(clicked()),this,SLOT(reject()));

}

NewProject::~NewProject()
{
    delete ui;
}

void NewProject::choose_project_dir()
{
    QFileDialog *file_dialog=new QFileDialog(this);
    file_dialog->setOption(QFileDialog::ShowDirsOnly);//设置显示选项
    file_dialog->setFileMode(QFileDialog::Directory);//设置文件模式
    file_dialog->setViewMode(QFileDialog::List);//设置显示模式
    //点击确定按钮
    if(file_dialog->exec()==QFileDialog::Accepted)
    {
        //获取新建项目路径
        new_project_dir_=file_dialog->selectedFiles().at(0);
        ui->projectDir->setText(new_project_dir_);//设置路径栏
    }
    //点取消则返回
    else
    {
        return;
    }
    delete file_dialog;
    file_dialog=NULL;
}

void NewProject::ok_new_project()
{
    //获取项目名和成员名
    new_project_name_=ui->projectName->text().trimmed();
    new_project_members_=ui->projectMembers->text().trimmed();

    //判断名字是否为空
    if( new_project_name_.isEmpty() || new_project_dir_.isEmpty()||new_project_members_.isEmpty() )
    {
        QMessageBox::information(this,"提示","表格未填完整，新建项目失败",QMessageBox::Yes);
    }
}


void NewProject::cancel_new_project_()
{
    QMessageBox::information(this,"提示","已取消新建项目",QMessageBox::Yes);
}
