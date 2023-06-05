#ifndef DATAMEANINGCORE_H
#define DATAMEANINGCORE_H

//#include <PythonQt.h>
#include "datarow.h"

class DataMeaningCore
{
public:
    DataMeaningCore();
    void callStatisticPy(QVector <DataRow> dataRows, QList <QByteArray> header);
    QVector <QVector <QString> > report();
private:
    QVector <QVector <QString> > reportValues;
};

#endif // DATAMEANINGCORE_H
