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
        for (int i = 1; i < content.size(); i++) {
            if (content[i].trimmed() != "") {
                dataRows.push_back(DataRow(content[i], header));
            }
        }
    }

    dataMeaningCore.callStatisticPy(dataRows, header);
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

QVector <QVector <QString>> DataMeaning::statisticMatrix() const
{
    QVector <QVector <QString>> result(header.size());

/*    QMap <QString, QString> types;

    for (int j = 0; j < header.size(); j++) {
        QMap <QString, int> variants;
        bool isNumerical = true;
        for (int i = 0; i < dataRows.size(); i++) {
            bool ok;
            int f = dataRows[i].value(header[j]).toFloat(&ok);
            if (!ok) {
                isNumerical = false;
            }
            if (variants.indexOf(dataRows[i].value(header[j])) >= 0) {
                variants[dataRows[i].value(header[j])]++;
            }
            else {
                variants[dataRows[i].value(header[j]), 1];
            }
        }
    }
    */

    for (int i = 0; i < result.size(); i++) {
        result[i].resize(4);
        result[i][0] = header[i];
        result[i][1] = "текст";
       // result[i][1] =
    }
    return result;
}

int DataMeaning::getFieldsSize() const
{
    return header.size();
}

QVector <QString> DataMeaning::fieldsStatisticHeader() const
{
    QVector <QString> result(4);
    result[0] = "Название";
    result[1] = "Тип";
    result[2] = "Максимальный и минимальный";
    result[3] = "Варианты";
    return result;
}

QVector <QString> DataMeaning :: fieldsHeader() const
{
    QVector <QString> result(header.size());
    for (int i = 0; i < result.size(); i++) {
        result[i] = header[i];
    }
    return result;
}

void DataMeaning :: removeRow(int index)
{
    dataRows.remove(index);
    dataMeaningCore.callStatisticPy(dataRows, header);
}
