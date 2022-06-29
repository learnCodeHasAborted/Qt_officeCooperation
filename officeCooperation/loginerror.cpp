#include "loginerror.h"
#include "ui_loginerror.h"

loginError::loginError(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginError)
{
    ui->setupUi(this);
}

loginError::~loginError()
{
    delete ui;
}
