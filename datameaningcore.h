#ifndef DATAMEANINGCORE_H
#define DATAMEANINGCORE_H

#include "array.h"
#include "datarow.h"

class DataMeaningCore
{
public:
    DataMeaningCore();
    void callStatisticPy(QVector <DataRow> dataRows, Array header, QString scriptname);
    void callStatisticPy(QVector <DataRow> dataRows, QString header, QString scriptname);
    QVector <Array> report();
private:
    QVector <Array> reportValues;
};

#endif // DATAMEANINGCORE_H
