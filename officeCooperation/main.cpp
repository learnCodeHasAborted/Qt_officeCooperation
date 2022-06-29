#include <QApplication>
#include"login.h"
#include"mytcpservice.h"
#include"myclient.h"
#include"doc.h"
#include"dialog.h"
#include"mainsiderbar.h"
#include "qboxlayout.h"
#include "qpushbutton.h"
#include"mainwindow.h"
#include<QWidget>
#include"friendwidget.h"
#include"addfriend.h"
#include"personcard.h"
#include"configuration.h"
#include"myapp.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);//适应高分辨率屏幕
    QApplication a(argc, argv);

    MyApp* ma = new MyApp();

//    MyApp* ma2 = new MyApp();

    return a.exec();
}
