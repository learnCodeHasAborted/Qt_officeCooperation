#ifndef TODO_H
#define TODO_H
#include<QTextBrowser>

class ToDo:public QTextBrowser
{
    Q_OBJECT
public:
    ToDo(int id, int IP, QString start, QString end, QString event, int colorId);
    int uid;
    int IP;
protected:
    virtual void mousePressEvent(QMouseEvent *event);//鼠标点击
signals:
    void forwardComplete(int uid,int IP);
};

#endif // TODO_H
