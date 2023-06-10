#include "datameaning.h"
#include <QDebug>

DataMeaning :: DataMeaning()
{
    m_pythonTypes["int64"] = "Целые";
    m_pythonTypes["float64"] = "Дробные";
    m_pythonTypes["object"] = "Символьные";
}

void DataMeaning::load(QList<QByteArray> content)
{
    if (content.size() == 0) {
        return;
    }

    QList <QByteArray> byteArray = content[0].split(',');
    m_header.resize(byteArray.size());
    for (int i = 0; i < byteArray.size(); i++) m_header[i] = ((QString)byteArray[i]).trimmed();

    if (content.size() > 1) {
        qDebug()<<(content.size()-1);
        for (int i = 1; i < content.size(); i++) {
            if (content[i].trimmed() != "") {
                m_dataRows.push_back(DataRow(content[i], m_header));
            }
        }
    }
//qDebug()<<"rows = "<<dataRows.size();
    m_dataMeaningCore.callStatisticPy(m_dataRows, m_header, "statistic");
    qDebug()<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    QVector <Array> report = m_dataMeaningCore.report();
    for (int i = 0; i < report.size(); i++) {
        for (int j = 0; j < report[i].size(); j++) {
            qDebug()<<i<<"\t"<<j<<"\t"<<report[i][j]<<"\t";
        }
        qDebug()<<"\n";
    }
qDebug()<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
    statisticValues.resize(m_header.size());
    for (int i = 0; i < statisticValues.size(); i++)
    {

        statisticValues[i].push_back(((QString)m_header[i]).trimmed());
        for (int j = 0; j < report.size(); j++)
        {
            if (j == 0)
            {
                qDebug()<<"report[j][i = "<<report[j][i];
            }
            if (report[j].size() > i)
            {
                QString val = report[j][i].right(report[j][i].size()-m_header[i].size()).trimmed();

                if (j == 0)
                {
                    m_headerTypes[m_header[i]] = val;
                    val = m_pythonTypes[val];
                }
                statisticValues[i].push_back(val);
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

    m_dataMeaningCore.callStatisticPy(m_dataRows, m_header, "statistic");
}

QVector <Array>  DataMeaning::loadedMatrix() const
{
    QVector <Array> result (m_dataRows.size());
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < m_header.size(); j++) {
            result[i].resize(m_header.size());
            result[i][j] = m_dataRows[i].value(m_header[j]);
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
    return m_header.size();
}

Array DataMeaning::fieldsStatisticHeader() const
{
    Array result(12);
    result[0] = "Название";
    result[1] = "Тип";
    result[2] = "Количество";
    result[3] = "Максимум";
    result[4] = "Минимум";
    result[5] = "Ср.значение";
    result[6] = "Ст.отклонение";
    result[7] = "Квартиль 25";
    result[8] = "Медиана";
    result[9] = "Квартиль 75";
    result[10] = "Разброс";
    result[11] = "Дисперсия";
    return result;
}

Array DataMeaning :: fieldsHeader() const
{
    Array result(m_header.size());
    for (int i = 0; i < result.size(); i++) {
        result[i] = m_header[i];
    }
    return result;
}

void DataMeaning :: removeRow(int index)
{
    m_dataRows.remove(index);
    m_dataMeaningCore.callStatisticPy(m_dataRows, m_header, "statistic");
}

void DataMeaning :: removeHeader(int index)
{
    QString key = m_header[index];
    m_header.removeAt(index);
}

QMap <QString, int> DataMeaning :: fieldKeys(QString field)
{
    int index = 0;
    QMap <QString, int> keys;
    for (int i = 0; i < m_dataRows.size(); i++)
    {
        if (!keys.contains(m_dataRows[i].value(field)))
        {
            keys[m_dataRows[i].value(field)] = index;
            index++;
        }
    }
    return keys;
}

Array DataMeaning :: values(QString field, bool isToNum)
{
    Array result(m_dataRows.size());
    if (isToNum)
    {

        QMap <QString, int> keys = fieldKeys(field);
        qDebug()<<keys;
        for (int i = 0; i < m_dataRows.size(); i++)
        {
            result[i] = QString::number(keys[m_dataRows[i].value(field)]);
        }
        qDebug()<<"result";
        qDebug()<<result;

    }
    else
    {
        for (int i = 0; i < m_dataRows.size(); i++)
        {
            result[i] = m_dataRows[i].value(field);
        }
    }

    return result;
}

QPair <QVector <double>, QVector <QString> > DataMeaning :: prepareToPredict(int fieldIndex)
{
    //    qDebug()<<fieldIndex<<"\t"<<(QString)m_header[fieldIndex];
    m_dataMeaningCore.callStatisticPy(m_dataRows, m_header[fieldIndex], "predict");
    qDebug()<<"******************************+++++++++++++++++++++++++++++++++++++";
    QVector <Array> report = m_dataMeaningCore.report();

     qDebug()<<report[0]<<"=================";
     QMap <QString, int> keys = fieldKeys(m_header[fieldIndex]);
     QVector <double> y;
     QVector <QString> x;
     for (int i = 1; i < report[0].size(); i++)
     {
         int delimIndex = report[0][i].lastIndexOf(' ');
         qDebug()<<report[0][i].left(delimIndex).trimmed()<<" = "<<report[0][i].right(report[0][i].size() - delimIndex).trimmed();
         if (!report[0][i].left(delimIndex).trimmed().isEmpty())
         {
             x.push_back(report[0][i].left(delimIndex).trimmed());
             y.push_back(report[0][i].right(report[0][i].size() - delimIndex).trimmed().toDouble());
         }
     }
    return QPair <QVector <double>, QVector <QString> > (y, x);

}

bool DataMeaning :: isSymbolHeaderField(int fieldIndex)
{
    return (m_headerTypes[m_header[fieldIndex]] == "object");
}
