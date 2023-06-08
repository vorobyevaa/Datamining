#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QVector>
#include <QtCharts>

class Chart {
public:
    Chart(QWidget * parent);
    void createChart(QVector <double> values, QVector <double> second, QVector <double> bords, double a);

    void createChart(QVector <QVector <QPair <double, double > > > values, int index, QString color, QString bcolor);
    void createChart(QVector <QVector <QPair <double, double > > > values, QString color, QString bcolor);
    void setTitle(QString title, QPair <QString, QString> caption);

private:
    QWidget * m_parent;
    QPair <QString, QString> m_caption;

    QChart *chart;

    int type;
};

#endif // CHART_H
