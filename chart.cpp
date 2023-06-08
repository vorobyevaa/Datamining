#include "chart.h"

#include <QtDebug>

using namespace QtCharts;
#include <QBarSet>

void Chart :: createChart(QVector <QVector <QPair <double, double > > > values, int index, QString color, QString bcolor)
{
    this->type = index;
    QMap <QString, QString> colors;
    colors["красный"] = "red";
    colors["синий"] = "blue";
    colors["цвет госпожи лапули"] = "gold";
    createChart(values, colors[color], colors[bcolor]);
}

void Chart :: createChart(QVector <QVector <QPair <double, double > > > values, QString color, QString bcolor)
{
    chart = new QChart();
    chart->setBackgroundBrush(QBrush(QColor(bcolor)));
    chart->legend()->hide();
    chart->removeAllSeries();


  QAbstractAxis * axisX = new QValueAxis();
   axisX->setTitleText(m_caption.first);
     //  axisX.setRange(0, 30)
       //axisX.setLabelFormat("%.1f")
    //   axisX.setTickCount(7)

   QAbstractAxis * axisY = new QValueAxis();
           axisY->setTitleText(m_caption.second);
     //  axisY.setRange(0, 100)
     //  axisY.setLabelFormat("%d")
     ////  axisY.setMinorTickCount(5)

    for (int k = 0; k < values.size(); k++)
    {
       QXYSeries *series;
       switch (type) {
       case 0:
           series = new QLineSeries();
           break;
       case 1:
           series = new QSplineSeries();
           break;
       case 2:
           series = new QScatterSeries();
            break;
       }


     // series->setUseOpenGL(true);
       series->setColor(QColor(color));
       series->setName(" " + QString::number(k));
       for (int i = 0; i < values[k].size(); i++)
       {
         series->append(values[k][i].first, values[k][i].second);
       }
       chart->addSeries(series);

     //  series->attachAxis(axisX);
       //     series->attachAxis(axisY);
    }

    chart->createDefaultAxes();

    QChartView *chartView = new QChartView(chart, m_parent);
    chartView->setGeometry(0,0,m_parent->size().width(),m_parent->size().height());
    chartView->setRenderHint(QPainter::Antialiasing);

  // chart->addAxis(axisX, Qt::AlignLeft);
    //   chart->addAxis(axisY, Qt::AlignLeft);
//
    chartView->show();
}

void Chart :: setTitle(QString title, QPair <QString, QString> caption)
{
    chart->setTitle(title);
    m_caption = caption;
}

void Chart :: createChart(QVector <double> values, QVector <double> second, QVector <double> bords, double a)
{
    QBarSet *set0 = new QBarSet("");//(m_caption == "") ? "Распределение сгенерированных чисел" : m_caption);
    QBarSet *set1 = new QBarSet("Заданные вероятности");

    // максимальное значение (для выставления высоты графика)
    double max = 0;
    for (int i = 0; i < values.size(); i++) {
        *set0 << values[i];
        double pm = values[i];//ui->tableWidget->item(i, 1)->text().toDouble();
        if (second.size() > 0) {
            if (second[i] > values[i]) pm = second[i];
            *set1 << second[i];
        }
        max = (max <pm) ? pm : max;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set0);

    QBarSeries *series1 = new QBarSeries();
    if (second.size() > 0)
    {
        series1->append(set1);
    }

    chart = new QChart();
    chart->addSeries(series);
    if (second.size() > 0) chart->addSeries(series1);
    chart->setTitle("Гистограммы распределения");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    for (int i = 0; i < values.size(); i++) {
        categories <<  ("("+QString::number((i == 0) ? a : bords[i-1]) + "; " + QString::number(bords[i])+"]");
    }
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    if (second.size() > 0) series1->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,max*1.1);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    if (second.size() > 0) series1->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);


    QChartView *chartView = new QChartView(chart, m_parent);
    chartView->setGeometry(0,0,m_parent->size().width(),m_parent->size().height());
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->show();
}

Chart :: Chart(QWidget * parent)
{
    m_parent = parent;
}
