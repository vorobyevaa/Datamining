#ifndef ARRAY_H
#define ARRAY_H

#include <QVector>
#include <QString>

class Array : public QVector <QString>
{
public:
    Array() {};
    Array(int size);
    QString implode(QString delimiter);
};

#endif // ARRAY_H
