#ifndef PTABLE_H
#define PTABLE_H

#include <QTableWidget>

class Ptable : public QTableWidget
{
    Q_OBJECT
public:
    Ptable(QWidget * owner = 0);
    void setValues(QVector <QVector <double> > values);
    void setValues(QVector <QPair <double, double> > values, double a);
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

private slots:
    void sl_cellClicked(int row, int column);

};

#endif
