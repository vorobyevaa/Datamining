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
    qDebug()<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    QVector <QVector <QString> > report = dataMeaningCore.report();
    for (int i = 0; i < report.size(); i++) {
        for (int j = 0; j < report.size(); j++) {
            qDebug()<<report[i][j]<<"\t";
        }
        qDebug()<<"\n";
    }
qDebug()<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
     statisticValues.resize(header.size());
    for (int i = 0; i < statisticValues.size(); i++) {
        statisticValues[i].push_back(((QString)header[i]).trimmed());
        for (int j = 0; j < report.size(); j++) {
            qDebug()<<"a  "<<i<<"\t"<<j;
            if (report[j].size() > i) {
                qDebug()<<"b";
            statisticValues[i].push_back(report[j][i].right(report[j][i].size()-((QString)header[i]).trimmed().size()).trimmed());
            qDebug()<<"c "<<i;
            }
            else {
                qDebug()<<"c "<<i;
                statisticValues[i].push_back("");
                qDebug()<<"d";
            }
        }
    }
    qDebug()<<"--------------------------------------------------------------";
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
    return statisticValues;

}

int DataMeaning::getFieldsSize() const
{
    return header.size();
}

QVector <QString> DataMeaning::fieldsStatisticHeader() const
{
    QVector <QString> result(5);
    result[0] = "Название";
    result[1] = "Максимум";
    result[2] = "Минимум";
    result[3] = "Тип";
    result[4] = "Варианты";
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

void DataMeaning :: removeHeader(int index)
{
    QString key = header[index];
    header.removeAt(index);
}
