#ifndef MYAPP_H
#define MYAPP_H
#include<QObject>
#include"login.h"
#include"register.h"
#include"mainwindow.h"

class MyApp:public QObject
{
    Q_OBJECT
public:
    MyApp();
    ~MyApp();
private:
    login* lg=nullptr;
    Register* rg=nullptr;
    MainWindow* mw=nullptr;

    void newLogin();
    void newRegister();
    void newMainWindow(int _id, QString _username);
    void login_success_slots(int _id, QString _username);
    void new_register_slots();
    void back_login_slots();
    void exit_slots();
};

#endif // MYAPP_H
