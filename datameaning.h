#ifndef DATAMEANING_H
#define DATAMEANING_H

#include <QByteArray>
#include <QList>
#include <QVector>
#include "array.h"
#include "datarow.h"
#include "datameaningcore.h"
#include "report.h"

class DataMeaning
{
public:
    DataMeaning();
    void load(QList<QByteArray> content);
    QVector <Array> loadedMatrix() const;
    QVector <Array> statisticMatrix() const;
    Array values(QString field, bool isToNum);
    int getFieldsSize() const;
    Array fieldsHeader() const;
    Array fieldsStatisticHeader() const;
    void removeRow(int index);
    void removeHeader(int index);
    QPair <QVector <double>, QVector <QString> > prepareToPredict(int fieldIndex);
    bool isSymbolHeaderField(int fieldIndex);
    QMap <QString, int> fieldKeys(QString field) ;
    Report createReport(QString models);
private:
    QVector <DataRow> m_dataRows;
    Array m_header;
    DataMeaningCore m_dataMeaningCore;
    QVector <Array> statisticValues;
    QMap <QString, QString> m_pythonTypes;
    QMap <QString, QString> m_headerTypes;
};

#endif // DATAMEANING_H
