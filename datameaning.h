#ifndef DATAMEANING_H
#define DATAMEANING_H

#include <QByteArray>
#include <QList>
#include <QVector>
#include "array.h"
#include "datarow.h"
#include "datameaningcore.h"

class DataMeaning
{
public:
    DataMeaning();
    void load(QList<QByteArray> content);
    QVector <Array> loadedMatrix() const;
    QVector <Array> statisticMatrix() const;
    Array values(QString field);
    int getFieldsSize() const;
    Array fieldsHeader() const;
    Array fieldsStatisticHeader() const;
    void removeRow(int index);
    void removeHeader(int index);

    void prepareToPredict(int fieldIndex);
private:
    QVector <DataRow> dataRows;
    QList <QByteArray> header;
    DataMeaningCore dataMeaningCore;
    QVector <Array> statisticValues;
};

#endif // DATAMEANING_H
