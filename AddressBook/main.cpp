#include "addressbook.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AddressBook w;
    w.setObjectName("addressbook");
    w.ReadFromFile();
    w.setStyleSheet("#addressbook{border-image:url(C://Users//hello//Desktop//bg.png);}");
    w.show();

    return a.exec();
}
