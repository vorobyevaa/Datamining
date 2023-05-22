#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QVector>
#include <QtCharts>

class Chart {
public:
    Chart(QWidget * parent, QString caption = "");
    void createChart(QVector <double> values, QVector <double> second, QVector <double> bords, double a);

    void createChart(QVector <QVector <QPair <double, double > > > values);
    void setTitle(QString title);

private:
    QWidget * m_parent;
    QString m_caption;

    QChart *chart;
};

#endif // CHART_H
