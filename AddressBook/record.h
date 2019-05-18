#ifndef RECORD_H
#define RECORD_H

#include <QString>

using namespace std;

class Record
{
public:
    Record() = default;
    Record(QString, QString, QString, QString, QString);

    QString name;
    QString phone_num;
    QString relation;
    QString province;
    QString city;

    bool operator<(const Record &rhs);
};

#endif // RECORD_H
