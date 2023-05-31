#include "datarow.h"
#include <QStringList>

DataRow::DataRow()
{

}

DataRow::DataRow(QString content, QList <QByteArray> header)
{
    QStringList values = content.split(',');
    for (int i = 0; i < values.size(); i++) {
        this->values[header[i]] = values[i];
    }
}

QString DataRow::value(QString key) const {
    return values[key];
}
