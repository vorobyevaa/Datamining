#ifndef REPORT_H
#define REPORT_H

#include <QString>
#include "array.h"
#include <QJsonObject>

class Report
{
public:
    Report(QString value);
    Array keys();
    Array keys(QString parentKey);
    QVector <Array> values(QString parentKey);
private:
    QString m_content;
    QJsonObject m_value;
};

#endif // REPORT_H
