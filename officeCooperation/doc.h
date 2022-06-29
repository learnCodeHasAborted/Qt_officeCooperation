#ifndef DOC_H
#define DOC_H

#include<QMainWindow>
#include<qstring.h>
#include<QString>
#include<QLineEdit>
#include<QTextCharFormat>
#include<QAction>
#include <QSplitter>
namespace Ui {
class doc;
}

class doc : public QMainWindow
{
    Q_OBJECT

public:
    explicit doc(QWidget *parent = 0);
    ~doc();
    QString fileName;
    QString curFile;
    bool isSaved;
    bool close;
    void loadFile(QString fileNames);
private slots:
    void new_project();//新建项目菜单
    void open_project();//打开项目菜单
    void on_action_triggered();
    void do_file_SaveAS();
    void do_file_Save();
    void do_file_SaveOrNot();
    bool saveFile(const QString&fileName);
    void show_findText();
    void close_findhangshu();
    void on_action_Open_triggered();
    void on_action_Save_triggered();
    void on_action_SaveAs_triggered();

    void on_action_Color_triggered();

    void on_action_Close_triggered();

    void on_action_Cancel_triggered();

    void on_action_Cut_triggered();

    void on_action_Copy_triggered();

    void on_action_Paste_triggered();

    void on_action_Delete_triggered();

    void on_action_About_triggered();

    void on_action_Font_triggered();

    void on_action_Italic_triggered();

    void on_action_SelectAll_triggered();

    void on_action_ShowTime_triggered();


    void on_action_Find_triggered();

    void on_action_Exit_triggered();

    void on_action_Underline_triggered();

    void on_action_LAlign_triggered();

    void on_action_RAlign_triggered();

    void on_action_CAlign_triggered();

    void on_action_JAlign_triggered();

private:
    Ui::doc *ui;
    QLineEdit *find_textLineEdit=nullptr;
    QAction *centerAction=nullptr;
    QVector<QString> project_name_;//项目名称
    QVector<QString> pro_path_;//项目文件路径(pro文件)
    QVector<QString> project_dir_;//项目目录
    QVector<QString> excute_dir_;//可执行文件目录(在项目中的目录)
    QSplitter *hsplitter=nullptr;//水平分割器
    QSplitter *vsplitter=nullptr;//垂直分割器


};

#endif // DOC_H
