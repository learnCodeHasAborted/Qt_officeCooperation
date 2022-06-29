#ifndef CONTROLLERLOGREGISTER_H
#define CONTROLLERLOGREGISTER_H
#include"login.h"
#include"register.h"

class ControllerLogRegister
{
    Q_OBJECT
public:
    ControllerLogRegister();
    login* log=nullptr;
    Register* reg = nullptr;
private slots:
    void verify();
    void getUsername(QString text);
    void getPwd(QString text);
    void showRegister();
};

#endif // CONTROLLERLOGREGISTER_H
