#include "doc.h"
#include "ui_doc.h"
#include"QDateTime"
#include<QFile>
#include<QString>
#include<QFileDialog>
#include<QFileInfo>
#include<QTextStream>
#include<QMessageBox>
#include<QTextStream>
#include<QTextCharFormat>
#include<QTextEdit>
#include<QFont>
#include<QFontDialog>
#include<QColorDialog>
#include<QColor>
#include<QPushButton>
#include<QTextCharFormat>
#include <QTimer>
#include <QGridLayout>
#include <QProcess>
#include "newproject.h"
doc::doc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::doc)
{
    ui->setupUi(this);
    isSaved=false;
    close=false;
    QString curFile = tr("项目编辑.txt");
    ui->treeWidget->setHeaderLabel(tr("项目-参与者"));
    setWindowTitle(curFile);
    this->setWindowIcon(QIcon(":/image/icons48.png"));

    //设置水平和垂直分割器，界面布局
    hsplitter=new QSplitter;//水平
    vsplitter=new QSplitter;//垂直
    vsplitter->setOrientation(Qt::Vertical);
    setCentralWidget(hsplitter);
    //注意部件顺序
    hsplitter->addWidget(ui->treeWidget);
    hsplitter->addWidget(ui->textEdit);

    //新建项目信号槽
    connect(ui->newProject,SIGNAL(triggered()),this,SLOT(new_project()));
    //打开项目信号槽
    connect(ui->openProject,SIGNAL(triggered()),this,SLOT(open_project()));
}

doc::~doc()
{
    delete ui;
}
void doc::do_file_SaveAS(){
    QString fileName=QFileDialog::getSaveFileName(this,tr("另存为"),curFile);

    if(!fileName.isEmpty()){
          saveFile(fileName);
    }

}

void doc::do_file_Save(){
    if(isSaved){
        saveFile(curFile);
    }
    else{

        do_file_SaveAS();
    }
}
void doc::do_file_SaveOrNot(){
    if(ui->textEdit->document()->isModified()){
        QMessageBox box;
        box.setWindowTitle(tr("Warning"));
        box.setIcon(QMessageBox::Warning);
        box.setText(curFile+tr("是否保存？"));
        box.setStandardButtons(QMessageBox::Yes);
        do_file_Save();
    }

}
bool doc::saveFile(const QString&fileName){
    QFile file(fileName);
            if(!file.open(QFile::WriteOnly|QFile::Text)){

        return false;
    }
    QTextStream out(&file);
    out<<ui->textEdit->toPlainText();
    isSaved=true;
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}


//新建文件
void doc::on_action_triggered()
{
    do_file_SaveOrNot();
    isSaved=false;
    curFile=tr("记事本.txt");
    setWindowTitle(curFile);
    ui->textEdit->clear();
    ui->textEdit->setVisible(true);
}
//打开文件 action 2
void doc::on_action_Open_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this);
    loadFile(filename);
}
//本地连接
void doc::loadFile(QString filename){
    printf("file name:%s\n",filename.data());

    QFile file(filename);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream textStream(&file);
        while(!textStream.atEnd())
        {
            ui->textEdit->append(textStream.readLine());
            printf("read line\n");
        }
        printf("end\n");
    }
    }
//保存文件 action 3
void doc::on_action_Save_triggered()
{
    if(isSaved){
        saveFile(curFile);
    }
    else{

        do_file_SaveAS();
    }
}
//另存为文件 action 4
void doc::on_action_SaveAs_triggered()
{
    QString fileName=QFileDialog::getSaveFileName(this,tr("另存为"),curFile);

    if(!fileName.isEmpty()){
          saveFile(fileName);
    }

}
//字体颜色 action 16
void doc::on_action_Color_triggered()
{
    QColor color=QColorDialog::getColor(Qt::red,this);

        if(color.isValid())
        {
            QTextCharFormat fmt;
                fmt.setForeground(color);
                ui->textEdit->mergeCurrentCharFormat(fmt);
        }
}
//关闭文件 action 5

void doc::on_action_Close_triggered()
{
    if(close){
          QMessageBox::information(this,"提示","文件尚未保存，关闭");
      }else{
    ui->textEdit->close();
    }
}
//撤销 action 6
void doc::on_action_Cancel_triggered()
{
   ui->textEdit->undo();
}
//剪切 action 7
void doc::on_action_Cut_triggered()
{
    ui->textEdit->cut();
}
//复制 action 8
void doc::on_action_Copy_triggered()
{
    ui->textEdit->copy();
}
//粘贴 action 9
void doc::on_action_Paste_triggered()
{
    ui->textEdit->paste();
}
//删除 action 10
void doc::on_action_Delete_triggered()
{
    ui->textEdit->redo();
}

//全选 action 13
void doc::on_action_SelectAll_triggered()
{
    ui->textEdit->selectAll();
}
//显示时间 action 14
void doc::on_action_ShowTime_triggered()
{
    QDateTime time =QDateTime::currentDateTime();
      QString str= time.toString("yyyy-MM-dd hh:mm:ss dddd");
      ui->textEdit->setText(str);
}


//查找 action 11
void doc::close_findhangshu()
{
    ui->gridLayoutWidget->close();
}
void doc::on_action_Find_triggered()
{
       QDialog *closefind=new QDialog(this);
       QDialog *findDlg=new QDialog(this);
       find_textLineEdit=new QLineEdit(findDlg);
       QPushButton *find_Bth=new QPushButton(tr("查找下一个"),findDlg);
       QPushButton *close_find=new QPushButton(tr("关闭"),closefind);
       ui->gridLayout->addWidget(find_textLineEdit);
       ui->gridLayout->addWidget(find_Bth);
       ui->gridLayout->addWidget(close_find);
       connect(find_Bth,SIGNAL(clicked()),this,SLOT(show_findText()));
       connect(close_find,SIGNAL(clicked()),this,SLOT(close_findhangshu()));
    }
void doc::show_findText()
{
    QString findText=find_textLineEdit->text();
    if(!ui->textEdit->find(findText,QTextDocument::FindBackward))
    {
        QMessageBox::warning(this,tr("查找"),tr("找不到 %1").arg(findText));

    }
}
//退出 action 12
void doc::on_action_Exit_triggered()
{
     delete ui->textEdit;
}

//关于 action 17
void doc::on_action_About_triggered()
{
    //ui->textEdit->setText(tr("About Message Box"));
    QMessageBox::about(this,tr("About"),tr("这是一个记事本，作者：咕咕咕"));
    return;

}
//字体 action 15
void doc::on_action_Font_triggered()
{
    bool ok;
       QFont currentFont=QFontDialog::getFont(&ok);
       if(ok){
           ui->textEdit->setFont(currentFont);
       }


}
//字体倾斜 action 18
void doc::on_action_Italic_triggered()
{
    QTextCharFormat fmt;
        fmt.setFontItalic(ui->action_Italic->isChecked());
        ui->textEdit->mergeCurrentCharFormat(fmt);

}
//下划线 action 19
void doc::on_action_Underline_triggered()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(ui->action_Underline->isChecked());
   ui->textEdit->mergeCurrentCharFormat(fmt);
}

//左对齐 action 20
void doc::on_action_LAlign_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignLeft);

}
//右对齐 action 21
void doc::on_action_RAlign_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}

//居中 action 22
void doc::on_action_CAlign_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);


}
//两端对齐 action 23
void doc::on_action_JAlign_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignJustify);

}

void doc::new_project()
{
    NewProject project;
    //所有栏都填完，且按下确定按钮
    if(project.exec()==QDialog::Accepted)
    {
        //获取新建项目名
        QString project_name__=project.get_new_project_name();
        //获取项目路径名
        QString project_dir__=project.get_new_project_dir();
        //获取可执行文件所在文件夹路径名
        //QString excute_dir__=project.get_excute_file_dir();
        //获取参与人员信息
        QString proj_members__=project.get_members();

        //新建项目失败
        if(project_name__.isEmpty() || project_dir__.isEmpty())
            return;
        //新建项目成功
        else
        {
            project_name_.append(project_name__);//添加项目名称
            //新建项目文件夹
            QDir dir(project_dir__);//项目文件夹所在目录
            dir.mkdir(project_name__);//创建以项目名为名字的目录
            QString _project_dir_=dir.absoluteFilePath(project_name__);//获取项目文件夹的绝对路径
            project_dir_.append(_project_dir_);//添加项目文件夹路径
            QDir project_dir(_project_dir_);

            //新建项目文件pro
            QFile pro_file( project_dir.filePath(project_name__+".pro") );
            loadFile(project_name__+".pro");
            pro_file.open(QFile::WriteOnly|QIODevice::Text);
            pro_path_.append(pro_file.fileName());//添加txt文件
            QTextStream pro_stream(&pro_file);
            pro_stream<<"Project was created successfully!\n";
            pro_stream<<"PROJECT NAME = "<<project_name__<<"\n";//添加项目名
            pro_stream<<"PROJECT DIR = "<<_project_dir_<<"\n";//添加项目路径
            pro_stream<<"PROJECT FILE NAME = "<<pro_file.fileName()<<"\n";//添加pro文件名的路径
            pro_stream<<"PROJECT MEMBER = "<<proj_members__<<Qt::endl;//添加参与人员信息
            pro_stream<<"Project Info:"<<Qt::endl;

            //创建树形条
            QTreeWidgetItem *item=new QTreeWidgetItem(ui->treeWidget,QStringList(project_name__));//添加节点

            //添加子节点
            QStringList members=proj_members__.split(',');
            QTreeWidgetItem **items;
            int num_members=members.count();
            items=new QTreeWidgetItem*[num_members];
            for(int i=0;i<num_members;++i){
                items[i]=new QTreeWidgetItem(item,QStringList(members[i]));
                item->addChild(items[i]);
            }
        }
    }

}

//打开项目槽函数
void doc::open_project()
{
    QString file_path_=QFileDialog::getOpenFileName(this,".打开项目");
    if(file_path_=="") return;
    QFile file(file_path_);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray str_line_;
    QString temp;
    QString proname;
    file.readLine();
    loadFile(file_path_);
    //项目名
    str_line_=file.readLine();
    proname=str_line_.mid(QString("PROJECT NAME = ").length(),str_line_.length()-QString("PROJECT NAME = ").length()-1);
    project_name_.append(proname);
    //创建树形条
    QTreeWidgetItem *item=new QTreeWidgetItem(ui->treeWidget,QStringList(proname));//添加节点
    //项目文件夹
    str_line_=file.readLine();
    temp=str_line_.mid(QString("PROJECT DIR = ").length(),str_line_.length()-QString("PROJECT DIR = ").length()-1);
    project_dir_.append(temp);
    //项目文件路径(pro)
    str_line_=file.readLine();
    temp=str_line_.mid(QString("PROJECT FILE NAME = ").length(),str_line_.length()-QString("PROJECT FILE NAME = ").length()-1);
    pro_path_.append(temp);
    //参与项目人员
    str_line_=file.readLine();
    temp=str_line_.mid(QString("PROJECT MEMBER = ").length(),str_line_.length()-QString("PROJECT MEMBER = ").length());
    //excute_dir_.append(temp);

    //添加子节点
    QStringList members=temp.split(',');
    QTreeWidgetItem **items;
    int num_members=members.count();
    items=new QTreeWidgetItem*[num_members];
    for(int i=0;i<num_members;++i){
        items[i]=new QTreeWidgetItem(item,QStringList(members[i]));
        item->addChild(items[i]);
    }

    ui->treeWidget->expandAll();//展开所有节点
}
