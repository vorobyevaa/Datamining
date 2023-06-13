#ifndef ARRAY_H
#define ARRAY_H

#include <QVector>
#include <QString>

class Array : public QVector <QString>
{
public:
    Array() {};
    Array(int size);
    Array(QStringList value);
    QString implode(QString delimiter);
    void operator = (QStringList value);
};

#endif // ARRAY_H
