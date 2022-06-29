#ifndef PASSWORDRESET_H
#define PASSWORDRESET_H

#include <QWidget>
#include"mydatabase.h"
#include<QTimer>
#include<QCloseEvent>

namespace Ui {
class PasswordReset;
}

class PasswordReset : public QWidget
{
    Q_OBJECT

public:
    explicit PasswordReset(int id,QWidget *parent = nullptr);
    ~PasswordReset();
protected:
    virtual void paintEvent(QPaintEvent* e);
    virtual void closeEvent(QCloseEvent* e);
private:
    Ui::PasswordReset *ui;

    MyDatabase* md=nullptr;
    QSqlDatabase db;
    QSqlQuery query;

    int id;
    int blinkCnt=0;
    QTimer* timer=nullptr;

    void init();

public slots:
    void confirm(QString);
    void changePassword();
    void blink();
};

#endif // PASSWORDRESET_H
