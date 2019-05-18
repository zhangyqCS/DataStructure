#include "mainwindow.h"
#include <QApplication>
#include "rbtree.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("RedBlackTree");
    w.setObjectName("MainWindow");
    w.setStyleSheet("#MainWindow{border-image:url(C://Users//hello//Desktop//bg.png);}");
    w.show();

    return a.exec();
}
