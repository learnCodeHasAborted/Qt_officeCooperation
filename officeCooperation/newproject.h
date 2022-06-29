#ifndef NEWPROJECT_H
#define NEWPROJECT_H

#include <QDialog>

namespace Ui {
class NewProject;
}

class NewProject : public QDialog
{
    Q_OBJECT

public:
    explicit NewProject(QWidget *parent = nullptr);
    ~NewProject();


    //获得新建项目名
    QString get_new_project_name(){return new_project_name_;}
    //获得新建项目的目录
    QString get_new_project_dir(){return new_project_dir_;}
    //获取参与人员信息
    QString get_members(){return new_project_members_;}

private:
    Ui::NewProject *ui;


    QString new_project_name_;//新建项目名
    QString new_project_dir_;//新建项目文件夹路径
    QString new_project_members_;//项目成员


private slots:
    void choose_project_dir();//选择项目目录按钮
    void ok_new_project();//确定按钮
    void cancel_new_project_();//取消按钮

};

#endif // NEWPROJECT_H
