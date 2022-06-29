#ifndef MAINSIDERBAR_H
#define MAINSIDERBAR_H

#include"todolist.h"
#include "dialog.h"
#include "doc.h"
#include "personcard.h"
#include <QWidget>

namespace Ui {
class MainSiderBar;
}

class MainSiderBar : public QWidget
{
    Q_OBJECT

public:
    explicit MainSiderBar(int id, QWidget *parent = nullptr);
    ~MainSiderBar();

private:
    Ui::MainSiderBar *ui;
    int id;
    PersonCard* p=nullptr;
    doc* d=nullptr;
    Dialog* dia=nullptr;
    ToDoList* to = nullptr;

    void init();
public slots:
    void icon_slot();
    void forward();

signals:
    void forwardInit();
    void back_login_signals();
};

#endif // MAINSIDERBAR_H
