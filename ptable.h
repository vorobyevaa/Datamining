#ifndef PTABLE_H
#define PTABLE_H

#include <QTableWidget>
#include "array.h"

class Ptable : public QTableWidget
{
    Q_OBJECT
public:
    Ptable(QWidget * owner = 0);
    void setShift(int value);
    void setColumnTitles(Array titles);
    void setValues(QVector <Array> values);
    void setHeader(Array header);
    bool checkValues(bool showMessageFlag);
    QVector <QPair <double, double> > values() const;
    QVector <QVector <double> > allValues() const;
    QVector <double> p() const;
    double a() const;
    void rebuildForExperimental(QVector <QString> titles);
    void addThirdColumn();
    void setThirdValues(QVector <double> values);
private:
    void _createRow(int rowIndex);
    QVector <QPair <double, double> > m_values;
    double m_a;
    int m_shift;
    bool m_columnTitlesFlag;
    Array m_columnTitles;

private slots:
    void sl_cellClicked(int row, int column);

signals:
    void removeRowSignal(int index);

};

#endif

