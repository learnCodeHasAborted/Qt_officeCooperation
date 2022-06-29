#include "dialog.h"
#include "ui_dialog.h"
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlError>
#include<QSqlDatabase>
#include<QSqlField>
#include<QDebug>
#include"mydatabase.h"

Dialog::Dialog(int id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),uid(id)
{
    ui->setupUi(this);
    this->setWindowTitle("设定计划");
    this->setWindowIcon(QIcon(":/image/icons48.png"));
    IPlist.append(tr("1"));
    IPlist.append(tr("2"));
    IPlist.append(tr("3"));
    IPlist.append(tr("4"));

    md=new MyDatabase("dialog"+QString::number(id));//数据库初始化
    db=md->getDatabase();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pBton_shezhi_clicked()
{
    //星期一
    setTime[0][0] = ui->timestart1->time();
    setTime[0][1] = ui->timeend1->time();
    setTime[0][2] = ui->timestart2->time();
    setTime[0][3] = ui->timeend2->time();
    setTime[0][4] = ui->timestart3->time();
    setTime[0][5] = ui->timeend3->time();
    setTime[0][6] = ui->timestart4->time();
    setTime[0][7] = ui->timeend4->time();
    setEvent[0][0] = ui->lineEdit1->text();
    setEvent[0][1] = ui->lineEdit2->text();
    setEvent[0][2] = ui->lineEdit3->text();
    setEvent[0][3] = ui->lineEdit4->text();
    if(setTime[0][0].operator > (setTime[0][1])||
            setTime[0][2].operator >(setTime[0][3])||
            setTime[0][4].operator >(setTime[0][5])||
            setTime[0][6].operator >(setTime[0][7]))
    {
        QMessageBox::warning(this,"错误提示","星期一设置时间出错!",QMessageBox::Yes);

        if( setTime[0][2].operator >(QTime(0,0)) || setTime[0][4].operator >(QTime(0,0)) || setTime[0][6].operator >(QTime(0,0)) )
        {
            if(setTime[0][2].operator <(setTime[0][1])||
                setTime[0][4].operator <(setTime[0][3])||
                setTime[0][6].operator <(setTime[0][5]))
            {
                QMessageBox::warning(this,"错误提示","星期一设置时间出错!",QMessageBox::Yes);
            }
          }
    }
    else
    {
        QSqlQuery query1(db);
        if(setTime[0][0].operator > (QTime(0,0))){
            query1.exec("delete from Timetable where `uid`="+QString::number(uid)+" and IP in (0,1,2,3)");
        }

        for(int i=0;i<4;i++){
            if(setTime[0][2*i].operator == (QTime(0,0))){
                break;
            }
            query1.prepare("insert into Timetable (IP,start,end,event,uid) values(?,?,?,?,?)");
            query1.addBindValue(i);
            query1.addBindValue(setTime[0][i*2]);
            query1.addBindValue(setTime[0][i*2+1]);
            query1.addBindValue(setEvent[0][i]);
            query1.addBindValue(uid);
            query1.exec();
            query1.finish();
        }
        close();
    }
  //星期二
    setTime[1][0] = ui->timestart1_1->time();
    setTime[1][1] = ui->timeend1_1->time();
    setTime[1][2] = ui->timestart2_1->time();
    setTime[1][3] = ui->timeend2_1->time();
    setTime[1][4] = ui->timestart3_1->time();
    setTime[1][5] = ui->timeend3_1->time();
    setTime[1][6] = ui->timestart4_1->time();
    setTime[1][7] = ui->timeend4_1->time();
    setEvent[1][0] = ui->lineEdit5->text();
    setEvent[1][1] = ui->lineEdit6->text();
    setEvent[1][2] = ui->lineEdit7->text();
    setEvent[1][3] = ui->lineEdit8->text();
    if(setTime[1][0].operator > (setTime[1][1])||
            setTime[1][2].operator >(setTime[1][3])||
            setTime[1][4].operator >(setTime[1][5])||
            setTime[1][6].operator >(setTime[1][7]))
    {
        QMessageBox::warning(this,"错误提示","星期二设置时间出错!",QMessageBox::Yes);

        if( setTime[1][2].operator >(QTime(0,0)) || setTime[1][4].operator >(QTime(0,0)) || setTime[1][6].operator >(QTime(0,0)) )
        {
            if(setTime[1][2].operator <(setTime[1][1])||
                setTime[1][4].operator <(setTime[1][3])||
                setTime[1][6].operator <(setTime[1][5]))
            {
                QMessageBox::warning(this,"错误提示","星期二设置时间出错!",QMessageBox::Yes);
            }
          }
    }
    else
    {
        QSqlQuery query1(db);
        if(setTime[1][0].operator > (QTime(0,0))){
            query1.exec("delete from Timetable where `uid`="+QString::number(uid)+" and IP in (4,5,6,7)");
        }
        for(int i=0;i<4;i++){
            if(setTime[1][2*i].operator == (QTime(0,0))){
                break;
            }
            query1.prepare("insert into Timetable (IP,start,end,event,uid) values(?,?,?,?,?)");
            query1.addBindValue(4+i);
            query1.addBindValue(setTime[1][i*2]);
            query1.addBindValue(setTime[1][i*2+1]);
            query1.addBindValue(setEvent[1][i]);
            query1.addBindValue(uid);
            query1.exec();
            query1.finish();
        }

        close();

    }
    //星期三
    setTime[2][0] = ui->timestart1_2->time();
    setTime[2][1] = ui->timeend1_2->time();
    setTime[2][2] = ui->timestart2_2->time();
    setTime[2][3] = ui->timeend2_2->time();
    setTime[2][4] = ui->timestart3_2->time();
    setTime[2][5] = ui->timeend3_2->time();
    setTime[2][6] = ui->timestart4_2->time();
    setTime[2][7] = ui->timeend4_2->time();
    setEvent[2][0] = ui->lineEdit9->text();
    setEvent[2][1] = ui->lineEdit10->text();
    setEvent[2][2] = ui->lineEdit11->text();
    setEvent[2][3] = ui->lineEdit12->text();
    if(setTime[2][0].operator > (setTime[2][1])||
            setTime[2][2].operator >(setTime[2][3])||
            setTime[2][4].operator >(setTime[2][5])||
            setTime[2][6].operator >(setTime[2][7]))
    {
        QMessageBox::warning(this,"错误提示","星期三设置时间出错!",QMessageBox::Yes);

        if( setTime[2][2].operator >(QTime(0,0)) || setTime[2][4].operator >(QTime(0,0)) || setTime[2][6].operator >(QTime(0,0)) )
        {
            if(setTime[2][2].operator <(setTime[2][1])||
                setTime[2][4].operator <(setTime[2][3])||
                setTime[2][6].operator <(setTime[2][5]))
            {
                QMessageBox::warning(this,"错误提示","星期三设置时间出错!",QMessageBox::Yes);
            }
          }
    }
    else
    {
        QSqlQuery query1(db);
        if(setTime[2][0].operator > (QTime(0,0))){
            query1.exec("delete from Timetable where `uid`="+QString::number(uid)+" and IP in (8,9,10,11)");
        }
        for(int i=0;i<4;i++){
            if(setTime[2][2*i].operator == (QTime(0,0))){
                break;
            }
            query1.prepare("insert into Timetable (IP,start,end,event,uid) values(?,?,?,?,?)");
            query1.addBindValue(8+i);
            query1.addBindValue(setTime[2][i*2]);
            query1.addBindValue(setTime[2][i*2+1]);
            query1.addBindValue(setEvent[2][i]);
            query1.addBindValue(uid);
            query1.exec();
            query1.finish();
        }

        close();
    }

    //星期四

    setTime[3][0] = ui->timestart1_3->time();
    setTime[3][1] = ui->timeend1_3->time();
    setTime[3][2] = ui->timestart2_3->time();
    setTime[3][3] = ui->timeend2_3->time();
    setTime[3][4] = ui->timestart3_3->time();
    setTime[3][5] = ui->timeend3_3->time();
    setTime[3][6] = ui->timestart4_3->time();
    setTime[3][7] = ui->timeend4_3->time();
    setEvent[3][0] = ui->lineEdit13->text();
    setEvent[3][1] = ui->lineEdit14->text();
    setEvent[3][2] = ui->lineEdit15->text();
    setEvent[3][3] = ui->lineEdit16->text();
    if(setTime[3][0].operator > (setTime[3][1])||
            setTime[3][2].operator >(setTime[3][3])||
            setTime[3][4].operator >(setTime[3][5])||
            setTime[3][6].operator >(setTime[3][7]))
    {
        QMessageBox::warning(this,"错误提示","星期四设置时间出错!",QMessageBox::Yes);

        if( setTime[3][2].operator >(QTime(0,0)) || setTime[3][4].operator >(QTime(0,0)) || setTime[3][6].operator >(QTime(0,0)) )
        {
            if(setTime[3][2].operator <(setTime[3][1])||
                setTime[3][4].operator <(setTime[3][3])||
                setTime[3][6].operator <(setTime[3][5]))
            {
                QMessageBox::warning(this,"错误提示","星期四设置时间出错!",QMessageBox::Yes);
            }
          }
    }
    else
    {

        QSqlQuery query1(db);
        if(setTime[3][0].operator > (QTime(0,0))){
            query1.exec("delete from Timetable where `uid`="+QString::number(uid)+" and IP in (12,13,14,15)");
        }
        for(int i=0;i<4;i++){
            if(setTime[3][2*i].operator == (QTime(0,0))){
                break;
            }
            query1.prepare("insert into Timetable (IP,start,end,event,uid) values(?,?,?,?,?)");
            query1.addBindValue(12+i);
            query1.addBindValue(setTime[3][i*2]);
            query1.addBindValue(setTime[3][i*2+1]);
            query1.addBindValue(setEvent[3][i]);
            query1.addBindValue(uid);
            query1.exec();
            query1.finish();
        }
        close();
    }
    //星期五
    setTime[4][0] = ui->timestart1_4->time();
    setTime[4][1] = ui->timeend1_4->time();
    setTime[4][2] = ui->timestart2_4->time();
    setTime[4][3] = ui->timeend2_4->time();
    setTime[4][4] = ui->timestart3_4->time();
    setTime[4][5] = ui->timeend3_4->time();
    setTime[4][6] = ui->timestart4_4->time();
    setTime[4][7] = ui->timeend4_4->time();
    setEvent[4][0] = ui->lineEdit17->text();
    setEvent[4][1] = ui->lineEdit18->text();
    setEvent[4][2] = ui->lineEdit19->text();
    setEvent[4][3] = ui->lineEdit20->text();
    if(setTime[4][0].operator > (setTime[4][1])||
            setTime[4][2].operator >(setTime[4][3])||
            setTime[4][4].operator >(setTime[4][5])||
            setTime[4][6].operator >(setTime[4][7]))
    {
        QMessageBox::warning(this,"错误提示","星期五设置时间出错!",QMessageBox::Yes);

        if( setTime[4][2].operator >(QTime(0,0)) || setTime[4][4].operator >(QTime(0,0)) || setTime[4][6].operator >(QTime(0,0)) )
        {
            if(setTime[4][2].operator <(setTime[4][1])||
                setTime[4][4].operator <(setTime[4][3])||
                setTime[4][6].operator <(setTime[4][5]))
            {
                QMessageBox::warning(this,"错误提示","星期五设置时间出错!",QMessageBox::Yes);
            }
          }
    }
    else
    {

        QSqlQuery query1(db);
        if(setTime[4][0].operator > (QTime(0,0))){
            query1.exec("delete from Timetable where `uid`="+QString::number(uid)+" and IP in (16,17,18,19)");
        }
        for(int i=0;i<4;i++){
            if(setTime[4][2*i].operator == (QTime(0,0))){
                break;
            }
            query1.prepare("insert into Timetable (IP,start,end,event,uid) values(?,?,?,?,?)");
            query1.addBindValue(16+i);
            query1.addBindValue(setTime[4][i*2]);
            query1.addBindValue(setTime[4][i*2+1]);
            query1.addBindValue(setEvent[4][i]);
            query1.addBindValue(uid);
            query1.exec();
            query1.finish();
        }
        close();
    }
    //星期六
    setTime[5][0] = ui->timestart1_5->time();
    setTime[5][1] = ui->timeend1_5->time();
    setTime[5][2] = ui->timestart2_5->time();
    setTime[5][3] = ui->timeend2_5->time();
    setTime[5][4] = ui->timestart3_5->time();
    setTime[5][5] = ui->timeend3_5->time();
    setTime[5][6] = ui->timestart4_5->time();
    setTime[5][7] = ui->timeend4_5->time();
    setEvent[5][0] = ui->lineEdit21->text();
    setEvent[5][1] = ui->lineEdit22->text();
    setEvent[5][2] = ui->lineEdit23->text();
    setEvent[5][3] = ui->lineEdit24->text();
    if(setTime[5][0].operator > (setTime[5][1])||
            setTime[5][2].operator >(setTime[5][3])||
            setTime[5][4].operator >(setTime[5][5])||
            setTime[5][6].operator >(setTime[5][7]))
    {
        QMessageBox::warning(this,"错误提示","星期六设置时间出错!",QMessageBox::Yes);

        if( setTime[5][2].operator >(QTime(0,0)) || setTime[5][4].operator >(QTime(0,0)) || setTime[5][6].operator >(QTime(0,0)) )
        {
            if(setTime[5][2].operator <(setTime[5][1])||
                setTime[5][4].operator <(setTime[5][3])||
                setTime[5][6].operator <(setTime[5][5]))
            {
                QMessageBox::warning(this,"错误提示","星期六设置时间出错!",QMessageBox::Yes);
            }
          }
    }
    else
    {

        QSqlQuery query1(db);
        if(setTime[5][0].operator > (QTime(0,0))){
            query1.exec("delete from Timetable where `uid`="+QString::number(uid)+" and IP in (20,21,22,23)");
        }
        for(int i=0;i<4;i++){
            if(setTime[5][2*i].operator == (QTime(0,0))){
                break;
            }
            query1.prepare("insert into Timetable (IP,start,end,event,uid) values(?,?,?,?,?)");
            query1.addBindValue(20+i);
            query1.addBindValue(setTime[5][i*2]);
            query1.addBindValue(setTime[5][i*2+1]);
            query1.addBindValue(setEvent[5][i]);
            query1.addBindValue(uid);
            query1.exec();
            query1.finish();
        }
        close();
    }
    //星期日
    setTime[6][0] = ui->timestart1_6->time();
    setTime[6][1] = ui->timeend1_6->time();
    setTime[6][2] = ui->timestart2_6->time();
    setTime[6][3] = ui->timeend2_6->time();
    setTime[6][4] = ui->timestart3_6->time();
    setTime[6][5] = ui->timeend3_6->time();
    setTime[6][6] = ui->timestart4_6->time();
    setTime[6][7] = ui->timeend4_6->time();
    setEvent[6][0] = ui->lineEdit25->text();
    setEvent[6][1] = ui->lineEdit26->text();
    setEvent[6][2] = ui->lineEdit27->text();
    setEvent[6][3] = ui->lineEdit28->text();
    if(setTime[6][0].operator > (setTime[6][1])||
            setTime[6][2].operator >(setTime[6][3])||
            setTime[6][4].operator >(setTime[6][5])||
            setTime[6][6].operator >(setTime[6][7]))
    {
        QMessageBox::warning(this,"错误提示","星期日设置时间出错!",QMessageBox::Yes);

        if( setTime[6][2].operator >(QTime(0,0)) || setTime[6][4].operator >(QTime(0,0)) || setTime[6][6].operator >(QTime(0,0)) )
        {
            if(setTime[6][2].operator <(setTime[6][1])||
                setTime[6][4].operator <(setTime[6][3])||
                setTime[6][6].operator <(setTime[6][5]))
            {
                QMessageBox::warning(this,"错误提示","星期日设置时间出错!",QMessageBox::Yes);
            }
          }
    }
    else
    {

        QSqlQuery query1(db);
        if(setTime[6][0].operator > (QTime(0,0))){
            query1.exec("delete from Timetable where `uid`="+QString::number(uid)+" and IP in (24,25,26,27)");
        }
        for(int i=0;i<4;i++){
            if(setTime[6][2*i].operator == (QTime(0,0))){
                break;
            }
            query1.prepare("insert into Timetable (IP,start,end,event,uid) values(?,?,?,?,?)");
            query1.addBindValue(24+i);
            query1.addBindValue(setTime[6][i*2]);
            query1.addBindValue(setTime[6][i*2+1]);
            query1.addBindValue(setEvent[6][i]);
            query1.addBindValue(uid);
            query1.exec();
            query1.finish();
        }
        close();
    }

}

void Dialog::on_pBton_cancel_clicked()
{
    close();
}
