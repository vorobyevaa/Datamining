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
//qDebug()<<"rows = "<<dataRows.size();
    dataMeaningCore.callStatisticPy(dataRows, header, "statistic");
    qDebug()<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    QVector <QVector <QString> > report = dataMeaningCore.report();
    for (int i = 0; i < report.size(); i++) {
        for (int j = 0; j < report[i].size(); j++) {
            qDebug()<<i<<"\t"<<j<<"\t"<<report[i][j]<<"\t";
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
           //     qDebug()<<"b";
            statisticValues[i].push_back(report[j][i].right(report[j][i].size()-((QString)header[i]).trimmed().size()).trimmed());
           // qDebug()<<"c "<<i;
            }
            else {
            //    qDebug()<<"c "<<i;
                statisticValues[i].push_back("");
           //     qDebug()<<"d";
            }
        }
    }
   // qDebug()<<"--------------------------------------------------------------";
}

QVector <Array>  DataMeaning::loadedMatrix() const
{
    QVector <Array> result (dataRows.size());
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < header.size(); j++) {
            result[i].resize(header.size());
            result[i][j] = dataRows[i].value(header[j]);
        }
    }
    return result;
}

QVector <Array> DataMeaning::statisticMatrix() const
{
    qDebug()<<statisticValues;
    return statisticValues;

}

int DataMeaning::getFieldsSize() const
{
    return header.size();
}

Array DataMeaning::fieldsStatisticHeader() const
{
    Array result(11);
    result[0] = "Название";
    result[1] = "Максимум";
    result[2] = "Минимум";
    result[3] = "Тип";
    result[4] = "Варианты";
    result[5] = "Название";
    result[6] = "Максимум";
    result[7] = "Минимум";
    result[8] = "Тип";
    result[9] = "Варианты";
    result[10] = "Варианты";
    return result;
}

Array DataMeaning :: fieldsHeader() const
{
    Array result(header.size());
    for (int i = 0; i < result.size(); i++) {
        result[i] = header[i];
    }
    return result;
}

void DataMeaning :: removeRow(int index)
{
    dataRows.remove(index);
    dataMeaningCore.callStatisticPy(dataRows, header, "statistic");
}

void DataMeaning :: removeHeader(int index)
{
    QString key = header[index];
    header.removeAt(index);
}

Array DataMeaning :: values(QString field)
{
    Array result(dataRows.size());
    for (int i = 0; i < dataRows.size(); i++) {
        result[i] = dataRows[i].value(field);
    }
    return result;
}

void DataMeaning :: prepareToPredict(int fieldIndex)
{
        qDebug()<<fieldIndex<<"\t"<<(QString)header[fieldIndex];
    dataMeaningCore.callStatisticPy(dataRows, (QString)header[fieldIndex], "predict");
}
