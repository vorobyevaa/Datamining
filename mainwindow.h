#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ptable.h"
#include "chart.h"
#include "datameaning.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void loadChartSelectors();

private slots:
    void importFile();
    void saveStatistic();
    void about();
    void support();
    void exit();
    void removeLoadedDataRow(int index);
    void removeStatisticDataRow(int index);
    void buildChart();
    void selectSecondDataColumn(int index);
private:
    Ui::MainWindow *ui;
    Ptable * ptLoadedData;
    Ptable * ptStaticticData;
    Chart * chChart;
    Ptable * ptSecondData;
    Chart * chSecondChart;
    DataMeaning dataMeaning;
};
#endif // MAINWINDOW_H


