#include "array.h"

Array :: Array(int size) : QVector <QString>(size)
{

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
