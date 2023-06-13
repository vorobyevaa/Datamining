#include "array.h"

Array :: Array(int size) : QVector <QString>(size)
{

}

Array :: Array(QStringList value)
{
    this->operator=(value);
}

QString Array :: implode(QString delimiter)
{
    QString result;
    for (int i = 0; i < size(); i++) {
        if (i > 0) result = result + delimiter;
        result = result + this->operator[](i);
    }
    return result;
}

void Array :: operator = (QStringList value)
{
    resize(value.size());
    int i = 0;
    foreach (QString val, value)
    {
        this->operator[](i) = val;
        i++;
    }
}
