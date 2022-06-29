#ifndef PICTURE_H
#define PICTURE_H

#include <QWidget>

class Picture:public QWidget
{
    Q_OBJECT
public:
    Picture(QString pre, int pic,QWidget* parent=nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent *event);//鼠标点击

private:
    int picture;
    QPixmap *pixmap;

signals:
    void forwardPicture(int picture);
};

#endif // PICTURE_H
