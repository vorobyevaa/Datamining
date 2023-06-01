#ifndef DATAMEANING_H
#define DATAMEANING_H

#include <QByteArray>
#include <QList>
#include <QVector>
#include "datarow.h"
#include "datameaningcore.h"

class DataMeaning
{
public:
    DataMeaning();
    void load(QList<QByteArray> content);
    QVector <QVector <QString>> loadedMatrix() const;
    QVector <QVector <QString>> statisticMatrix() const;
    int getFieldsSize() const;
    QVector <QString> fieldsHeader() const;
    QVector <QString> fieldsStatisticHeader() const;
private:
    QVector <DataRow> dataRows;
    QList <QByteArray> header;
    DataMeaningCore dataMeaningCore;
};

#endif // DATAMEANING_H
