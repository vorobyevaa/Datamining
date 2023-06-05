#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  //  setWindowFlags(windowFlags() &(~Qt::WindowMaximizeButtonHint));
    ptLoadedData = new Ptable(ui->frame_table);
    ptStaticticData = new Ptable(ui->f_statistic);
    chChart = new Chart(ui->frame_chart);

    connect(ui->action_import, &QAction::triggered, this, &MainWindow::importFile);
    connect(ptLoadedData, SIGNAL(removeRowSignal(int)), this, SLOT(removeLoadedDataRow(int)));
    connect(ptStaticticData, SIGNAL(removeRowSignal(int)), this, SLOT(removeStatisticDataRow(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::importFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text (*.txt *.csv)"));
    qDebug()<<fileName;

    QFile file(fileName);
    if (fileName == ".fileName" || !file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, "Невозможно открыть файл", file.errorString());
        return;
    }
    else
    {
        QTextStream in(&file);
        dataMeaning.load(file.readAll().split('\n'));

        ptLoadedData->setHeader(dataMeaning.fieldsHeader());
        ptLoadedData->setValues(dataMeaning.loadedMatrix());

        ptStaticticData->setHeader(dataMeaning.fieldsStatisticHeader());
        ptStaticticData->setValues(dataMeaning.statisticMatrix());
    }
}


void MainWindow :: removeLoadedDataRow(int index)
{
    dataMeaning.removeRow(index);
    ptStaticticData->setValues(dataMeaning.statisticMatrix());
}

void MainWindow :: removeStatisticDataRow(int index)
{
     dataMeaning.removeHeader(index);
     ptLoadedData->setHeader(dataMeaning.fieldsHeader());
     ptLoadedData->setValues(dataMeaning.loadedMatrix());
}
