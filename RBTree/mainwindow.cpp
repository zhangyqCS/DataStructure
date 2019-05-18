#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::GetNum(int &i)
{
    bool ok;
    i = QInputDialog::getInt(this, tr("Prossing..."),
        tr("Number: "), 0, 0, 1000, 1, &ok);
    if(!ok) return false;
    return true;
}

void MainWindow::on_AddBtn_clicked()
{
    int num;

    if(!GetNum(num)) return;

    if(t.find(num))
        QMessageBox::warning(this, tr("Warning"), tr("Number Existing!"),QMessageBox::Abort);

    t.insert(num);

    QString str;

    t.print(str);

    ui->DisplyEdit->setText(str);

}

void MainWindow::on_DelBtn_clicked()
{
    int num;

    if(!GetNum(num)) return;

    if(!t.find(num))
        QMessageBox::warning(this, tr("Warning"), tr("Can't Find!"),QMessageBox::Abort);

    t.erase(num);

    QString str;

    t.print(str);

    ui->DisplyEdit->setText(str);

}

void MainWindow::on_ResetBtn_clicked()
{
    t.destroy(t.root());
    t.root() = nullptr;
    ui->DisplyEdit->setText("");
}
