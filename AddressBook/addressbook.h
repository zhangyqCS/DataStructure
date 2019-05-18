#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QMainWindow>
#include <QDebug>
#include <QInputDialog>
#include <Qfile>
#include <QMessageBox>
#include <QVector>
#include <QTextStream>
#include <vector>
#include <iostream>
#include <QMessageBox>
#include <string>
#include "record.h"
#include <cctype>

namespace Ui {
class AddressBook;
}

class AddressBook : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddressBook(QWidget *parent = 0);
    ~AddressBook();

    void SaveToFile();

    void ReadFromFile();

    bool GetTargetRcd(vector<int> &, int &);

    bool GetNewRcd(Record &);

private slots:
    void on_AddBtn_clicked();

    void on_DelBtn_clicked();

    void on_DisplayBtn_clicked();

    void on_ModifyBtn_clicked();

    void on_SrchEdit_textChanged(const QString &arg1);

    void on_HelpBtn_clicked();

private:
    Ui::AddressBook *ui;

    QVector<Record> records;
};

#endif // ADDRESSBOOK_H
