#include "myapp.h"

MyApp::MyApp()
{
    newLogin();
}

MyApp::~MyApp()
{
    delete lg;delete rg;delete mw;
}

void MyApp::newLogin()
{
    lg = new login();
    connect(lg,&login::login_success_signals, this, &MyApp::login_success_slots );
    connect(lg,&login::new_register_signals, this, &MyApp::new_register_slots );
    lg->show();
}

void MyApp::newRegister()
{
    rg = new Register();
    connect(rg,&Register::back_login_signals, this, &MyApp::back_login_slots );
    rg->show();
}

void MyApp::newMainWindow(int _id, QString _username)
{
    mw = new MainWindow(_id, _username);
    connect(mw,&MainWindow::back_login_signals, this, &MyApp::back_login_slots );
    connect(mw,&MainWindow::exit_signals, this, &MyApp::exit_slots);
    mw->show();
}

void MyApp::login_success_slots(int _id, QString _username)
{
    delete lg;lg=nullptr;
    newMainWindow(_id,_username);
}

void MyApp::new_register_slots()
{
    delete lg;lg=nullptr;
    newRegister();
}

void MyApp::back_login_slots()
{
    delete rg;delete mw;
    rg=nullptr;mw=nullptr;
    newLogin();
}

void MyApp::exit_slots()
{
    delete this;
}
