#ifndef LOGIN_H
#define LOGIN_H
#include"register.h"
#include <QWidget>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
    Ui::login* getUi();

protected:
    virtual void paintEvent(QPaintEvent *event);

private slots:
    void verify();
    void showRegister();

private:
    Ui::login *ui;
    void init();
    QString username="";
    QString pwd="";

signals:
    void login_success_signals(int _id,QString _username);
    void new_register_signals();
};

#endif // LOGIN_H
