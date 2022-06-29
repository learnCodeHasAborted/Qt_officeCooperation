#include "picture.h"
#include "qdebug.h"
#include <QLabel>

Picture::Picture(QString pre, int pic, QWidget *parent):QWidget(parent),picture(pic)
{
    if(pre=="icon") this->setFixedSize(QSize(100,100));
    else if(pre == "background") this->setFixedSize(QSize(200,100));

    QLabel* label = new QLabel(this);
    label->setFixedSize(this->size());
    pixmap = new QPixmap(":/image/"+pre+"/"+QString::number(picture)+".jpg");

    pixmap->scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    label->setScaledContents(true);
    label->setPixmap(*pixmap);
}

void Picture::mousePressEvent(QMouseEvent *event)
{
    emit forwardPicture(picture);
}
