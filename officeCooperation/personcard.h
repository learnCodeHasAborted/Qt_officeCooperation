#ifndef PERSONCARD_H
#define PERSONCARD_H

#include <QWidget>
#include"mydatabase.h"
#include"passwordreset.h"

namespace Ui {
class PersonCard;
}

class PersonCard : public QWidget
{
    Q_OBJECT

public:
    explicit PersonCard(int id, QWidget *parent = nullptr);
    ~PersonCard();
protected:
    virtual void closeEvent(QCloseEvent* e);
private:
    Ui::PersonCard *ui;

    MyDatabase* md=nullptr;
    QSqlDatabase db;
    QSqlQuery query;

    int id;

    QWidget* iw=nullptr;
    QWidget* bw=nullptr;
    PasswordReset* pw=nullptr;
    QPixmap *pixmap=nullptr;
    QPixmap *pixmap2=nullptr;

    void init();
public slots:
    void showIcon();
    void setIcon(int);
    void showBackground();
    void setBackground(int i);
    void setPassword();
    void logout();

signals:
    void forwardInit();
    void forwardLogout();
    void close_personcard_signals();
};

#endif // PERSONCARD_H
