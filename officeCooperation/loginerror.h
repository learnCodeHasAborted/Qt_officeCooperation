#ifndef LOGINERROR_H
#define LOGINERROR_H

#include <QDialog>

namespace Ui {
class loginError;
}

class loginError : public QDialog
{
    Q_OBJECT

public:
    explicit loginError(QWidget *parent = 0);
    ~loginError();

private:
    Ui::loginError *ui;
};

#endif // LOGINERROR_H
