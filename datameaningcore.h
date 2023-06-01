#ifndef DATAMEANINGCORE_H
#define DATAMEANINGCORE_H

#include <PythonQt.h>
#include "datarow.h"

class DataMeaningCore
{
public:
    DataMeaningCore();
    void callStatisticPy(QVector <DataRow> dataRows, QList <QByteArray> header);
private:
    PythonQtObjectPtr mainModule;
};

#endif // DATAMEANINGCORE_H
