#include <QCoreApplication>
#include"file.h"
#include"chat.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Chat* c = new Chat(25000);
    File* f= new File(26000);
    return a.exec();
}
