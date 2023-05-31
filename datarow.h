#ifndef DATAROW_H
#define DATAROW_H

#include <QByteArray>
#include <QList>
#include <QString>
#include <QMap>

class DataRow
{
public:
    DataRow();
    DataRow(QString content, QList <QByteArray> header);
    QString value(QString key) const;
private:
    QMap <QString, QString> values;
};

#endif // DATAROW_H
