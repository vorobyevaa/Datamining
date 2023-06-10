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
    colors["жёлтый"] = "gold";
    colors["коричневый"] = "brown";
    colors["чёрный"] = "black";
    colors["зелёный"] = "green";
    colors["белый"] = "white";
    colors["розовый"] = "pink";
    colors["серый"] = "grey";
    colors["голубой"] = "blue";
    createChart(values, colors[color], colors[bcolor]);
}

void Chart :: createChart(QVector <QVector <QPair <double, double > > > values, QString color, QString bcolor)
{
    chart = new QChart();
    chart->setBackgroundBrush(QBrush(QColor(bcolor)));
    chart->legend()->hide();
    chart->removeAllSeries();


 // QAbstractAxis * axisX = new QValueAxis();
 //  axisX->setTitleText(m_caption.first);
     //  axisX.setRange(0, 30)
       //axisX.setLabelFormat("%.1f")
    //   axisX.setTickCount(7)

  // QAbstractAxis * axisY = new QValueAxis();
     //      axisY->setTitleText(m_caption.second);
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

      // series->attachAxis(axisX);
           // series->attachAxis(axisY);


            // series->attachAxis(axisX);
              //    series->attachAxis(axisY);
              //    chart->setAxisX(axisX, series);
              //    chart->setAxisY(axisY, series);
    }

    chart->createDefaultAxes();
chart->axes(Qt::Horizontal).back()->setTitleText(m_caption.first);
chart->axes(Qt::Vertical).back()->setTitleText(m_caption.second);
    QChartView *chartView = new QChartView(chart, m_parent);
    chartView->setGeometry(0,0,m_parent->size().width(),m_parent->size().height());
    chartView->setRenderHint(QPainter::Antialiasing);

 //  chart->addAxis(axisX, Qt::AlignLeft);
     //  chart->addAxis(axisY, Qt::AlignLeft);
//
    chartView->show();
}

void Chart :: setTitle(QString title, QPair <QString, QString> caption)
{
        qDebug()<<"SUPERHER";
   // chart->setTitle(title);
        qDebug()<<"SUPERHER";
    m_caption = caption;
    qDebug()<<"SUPERHER";
    qDebug()<<caption;
}

void Chart :: createChart(QVector <double> values, QVector <QString> x, QString title)
{
    QBarSet *set1 = new QBarSet(title);

    // максимальное значение (для выставления высоты графика)
    double max = 0;
    for (int i = 0; i < values.size(); i++) {
        *set1 << values[i];
        double pm = values[i];//ui->tableWidget->item(i, 1)->text().toDouble();
        max = (max <pm) ? pm : max;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set1);

    chart = new QChart();
    chart->addSeries(series);

    chart->setTitle("Гистограммы распределения");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    for (int i = 0; i < values.size(); i++) {
        categories <<  x[i];
    }
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);


    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,max*1.1);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

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
