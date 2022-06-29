#include "todo.h"

ToDo::ToDo(int id, int ip,  QString start, QString end, QString event, int colorId):uid(id),IP(ip)
{
    this->setFont(QFont("Microsoft YaHei"));
    this->setFontPointSize(12);
    if(colorId++%2){this->setStyleSheet("background-color:rgb( 218,227,230);");}
    else{this->setStyleSheet("background-color:rgb( 255 ,250 ,240);");}
    this->append("开始时间："+start);
    this->append("截止时间："+end);
    this->append("待办事项："+event);
}

void ToDo::mousePressEvent(QMouseEvent *event)
{
    emit forwardComplete(uid,IP);
}
