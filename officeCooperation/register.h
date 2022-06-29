#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::Register *ui;
    void init();

private slots:
    void verify();
    void getUsername(QString text);
    void getPwd(QString text);
    void showLogin();
private:
    QString username="";
    QString pwd="";
signals:
    void back_login_signals();
};

#endif // REGISTER_H
