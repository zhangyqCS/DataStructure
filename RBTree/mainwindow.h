#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <rbtree.h>
#include <QString>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool GetNum(int &);

private slots:
    void on_AddBtn_clicked();

    void on_DelBtn_clicked();

    void on_ResetBtn_clicked();

private:
    RBTree t;
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
