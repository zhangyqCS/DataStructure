#include "addressbook.h"
#include "ui_addressbook.h"

AddressBook::AddressBook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddressBook)
{
    ui->setupUi(this);
}

AddressBook::~AddressBook()
{
    delete ui;
}

void AddressBook::ReadFromFile()
{
    QFile file("chenhc.txt");

    if(!file.open(QIODevice::ReadWrite |QIODevice::Text))
        qDebug() << file.errorString();
    QTextStream in(&file);

    int rcd_num = 5;

    while(1)
    {
        QString str[rcd_num];
        for(int i = 0; i < rcd_num; ++i)
        {
            str[i] = in.readLine();
        }
        if(str[rcd_num-1].size() == 0) break;

        records.push_back(Record(str[0], str[1], str[2], str[3], str[4]));
    }

    file.close();
}

void AddressBook::SaveToFile()
{
    QFile file("chenhc.txt");

        if(!file.open(QIODevice::WriteOnly |QIODevice::Text))
            qDebug() << file.errorString();
        QTextStream in(&file);

        for(int i = 0; i < records.size(); ++i)
        {
            in << records[i].name << "\n"
               << records[i].phone_num << "\n"
               << records[i].relation << "\n"
               << records[i].province << "\n"
               << records[i].city << "\n";
        }

        file.close();
}

bool AddressBook::GetTargetRcd(vector<int> &id, int &idx)
{
    bool ok;

    QString keywords = QInputDialog::getText(this, tr("Processing..."), tr("Key Words: "),
            QLineEdit::Normal, tr("ChenHC"), &ok);
    if(!ok) return false;

    string SrchStr = keywords.toStdString();

    QString DisplyStr;

    int cnt = 0;

    //find those records, and store their id
    for(int i = 0; i < records.size(); ++i)
    {
        if((signed)records[i].name.toStdString().find(SrchStr) != -1
        || (signed)records[i].phone_num.toStdString().find(SrchStr) != -1
        || (signed)records[i].relation.toStdString().find(SrchStr) != -1
        || (signed)records[i].province.toStdString().find(SrchStr) != -1
        || (signed)records[i].city.toStdString().find(SrchStr) != -1)
        {
            id.push_back(i);

            //transform int to char *
            char num[105];
            sprintf(num, "%d.\n", ++cnt);

            DisplyStr += QString(num) + "Name: " + records[i].name + '\n';
            DisplyStr += "PhoneNum: " + records[i].phone_num + '\n';
            DisplyStr += "Relation: " + records[i].relation + "\n";
            DisplyStr += "Province: " + records[i].province + "\n";
            DisplyStr += "City: " + records[i].city + "\n\n";
        }
    }
    DisplyStr += "Please input the index:";

    if(id.size() < 1)
    {
        QMessageBox::warning(this, tr("Warning"), tr("Your input is error!"),QMessageBox::Abort);
        return false;
    }

    QString Idx = QInputDialog::getText(this, tr("Processing..."), tr(DisplyStr.toStdString().c_str()),
            QLineEdit::Normal, tr("1"), &ok);
    if(!ok) return false;
    idx = Idx.toInt();

    //do for error input
    if(!(1 <= idx && idx <= (int)id.size()))
    {
        QMessageBox::warning(this, tr("Warning!"), tr("Your input is error!"),QMessageBox::Abort);
        return false;
    }

    return true;
}

bool AddressBook::GetNewRcd(Record &newrcd)
{
    bool ok;

    //add_name
    QString name = QInputDialog::getText(this, tr("Processing..."), tr("Name: "),
            QLineEdit::Normal, tr("ChenHC"), &ok);
    if(!ok) return false;

    //add_phone_number
    there:
    QString PhoneNum = QInputDialog::getText(this, tr("Processing..."), tr("Phone Number: "),
            QLineEdit::Normal, tr("110"), &ok);
    bool check = true;
    for(int i = 0; i < PhoneNum.size(); ++i)
        if(!isdigit(PhoneNum.toStdString()[i])) check = false;
    if(!check)
    {
        QMessageBox::warning(this, tr("Warning"), tr("Your input is not number!"),QMessageBox::Abort);
        goto there;
        //return false;
    }

    if(!ok) return false;

    //add_relation
    QStringList RelaList;
    RelaList << tr("Relative") << tr("Classmate") << tr("Acquaintance") << tr("Others");
    QString rela = QInputDialog::getItem(this, tr ("Processing..."), tr("Relation："), RelaList, 0, false, &ok);
    if(!ok) return false;

    //add_province
    QString prov = QInputDialog::getText(this, tr("Processing..."), tr("Province: "),
            QLineEdit::Normal, tr("Zhejiang"), &ok);
    if(!ok) return false;

    //add_city
    QString cit = QInputDialog::getText(this, tr("Processing..."), tr("City: "),
            QLineEdit::Normal, tr("Jinhua"), &ok);
    if(!ok) return false;

    newrcd = Record(name, PhoneNum, rela, prov, cit);

    return true;
}

void AddressBook::on_AddBtn_clicked()
{

    Record newrcd;
    bool ok = GetNewRcd(newrcd);

    if(!ok) return;

    records.push_back(newrcd);

    QMessageBox::information(this, tr("Result"), tr("Success!"),QMessageBox::Ok);

    SaveToFile();
}

void AddressBook::on_DelBtn_clicked()
{
    vector<int> id;
    int idx;

    bool ok = GetTargetRcd(id, idx);

    if(!ok) return;

    records.erase(records.begin() + id[idx-1]);

    QMessageBox::information(this, tr("Result"), tr("Success!"),QMessageBox::Ok);

    SaveToFile();
}

void AddressBook::on_DisplayBtn_clicked()
{
    QString DisplyStr;

    sort(records.begin(), records.end());
    SaveToFile();

    int cnt = 0;
    for(int i = 0; i < records.size(); ++i, ++cnt)
    {
        DisplyStr += "Name: " + records[i].name + '\n';
        DisplyStr += "PhoneNum: " + records[i].phone_num + '\n';
        DisplyStr += "Relation: " + records[i].relation + "\n";
        DisplyStr += "Province: " + records[i].province + "\n";
        DisplyStr += "City: " + records[i].city + "\n\n";
    }

    //deal with plural
    QString s;
    if(cnt > 1) s = "s";

    char num[105];
    sprintf(num, "%d ", cnt);

    DisplyStr = "There are " + QString(num) + "Record" + s + '\n' + DisplyStr;
    ui->DisplayEdit->setPlainText(DisplyStr);
}

void AddressBook::on_ModifyBtn_clicked()
{
    vector<int> id;
    int idx;

    bool ok = GetTargetRcd(id, idx);

    if(!ok) return;

    Record newrcd;

    ok = GetNewRcd(newrcd);
    if(!ok)  return;

    records[id[idx-1]] = newrcd;

    QMessageBox::information(this, tr("Result"), tr("Success!"),QMessageBox::Ok);

    SaveToFile();
}

void AddressBook::on_SrchEdit_textChanged(const QString &arg1)
{
    string SrchStr = ui->SrchEdit->text().toStdString();

    QString DisplyStr;

    if(SrchStr.size() == 0)
    {
        ui->DisplayEdit->setPlainText(DisplyStr);
        return;
    }

    int cnt = 0;
    for(int i = 0; i < records.size(); ++i)
    {
        if((signed)records[i].name.toStdString().find(SrchStr) != -1
        || (signed)records[i].phone_num.toStdString().find(SrchStr) != -1
        || (signed)records[i].relation.toStdString().find(SrchStr) != -1
        || (signed)records[i].province.toStdString().find(SrchStr) != -1
        || (signed)records[i].city.toStdString().find(SrchStr) != -1)
        {
            ++cnt;
            DisplyStr += "Name: " + records[i].name + '\n';
            DisplyStr += "PhoneNum: " + records[i].phone_num + '\n';
            DisplyStr += "Relation: " + records[i].relation + "\n";
            DisplyStr += "Province: " + records[i].province + "\n";
            DisplyStr += "City: " + records[i].city + "\n\n";
        }
    }

    QString s;
    if(cnt > 1) s = "s";

    char num[105];
    sprintf(num, "%d ", cnt);

    DisplyStr = "There are " + QString(num) + "Record" + s + '\n' + DisplyStr;
    ui->DisplayEdit->setPlainText(DisplyStr);
}

void AddressBook::on_HelpBtn_clicked()
{
    QFile file("help.txt");

    if(!file.open(QIODevice::ReadWrite |QIODevice::Text))
        qDebug() << file.errorString();
    QTextStream in(&file);

    QString cur, s;

    while(1)
    {
        cur = in.readLine();
        if(cur.size() == 0) break;
        s += cur + '\n';
    }

    QMessageBox::information(this, tr("Help"), tr(s.toStdString().c_str()),QMessageBox::Ok);

    file.close();
}
