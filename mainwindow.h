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

private slots:
    void importFile();

private:
    Ui::MainWindow *ui;
    Ptable * ptLoadedData;
    Ptable * ptStaticticData;
    Chart * chChart;


    DataMeaning dataMeaning;
};
#endif // MAINWINDOW_H
