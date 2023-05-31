#include "datameaning.h"
#include <QDebug>

DataMeaning :: DataMeaning()
{

}

void DataMeaning::load(QList<QByteArray> content)
{

    if (content.size() == 0) {
        return;
    }

    header = content[0].split(',');
    if (content.size() > 1) {
        qDebug()<<(content.size()-1);
        dataRows.resize(content.size()-1);
        for (int i = 1; i < content.size(); i++) {
            dataRows[i-1] = DataRow(content[i], header);
       }
   }
}

QVector <QVector <QString>>  DataMeaning::loadedMatrix() const
{
    QVector <QVector <QString>> result (dataRows.size());
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < header.size(); j++) {
            result[i].resize(header.size());
            result[i][j] = dataRows[i].value(header[j]);
        }
    }
    return result;
}

int DataMeaning::getFieldsSize() const
{
    return header.size();
}

QVector <QString> DataMeaning :: fieldsHeader() const {
    QVector <QString> result(header.size());
    for (int i = 0; i < result.size(); i++) {
        result[i] = header[i];
    }
    return result;
}
