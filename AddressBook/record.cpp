#include "record.h"

Record::Record(QString s1, QString s2, QString s3, QString s4, QString s5)
    : name(s1), phone_num(s2), relation(s3), province(s4), city(s5)
{

}

bool Record::operator<(const Record &rhs)
{
    //transform name to standard
    string a(name.toStdString()), b(rhs.name.toStdString());

    for(char &ch : a)
    {
        ch = tolower(ch);
    }

    for(char &ch : b)
    {
        ch = tolower(ch);
    }

    return a < b;
}
