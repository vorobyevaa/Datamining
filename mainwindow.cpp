#include "mainwindow.h"
#include "about.h"
#include "support.h"
#include "ui_mainwindow.h"
#include <QPair>

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
    connect(ui->action_save, &QAction::triggered, this, &MainWindow::saveStatistic);
    connect(ui->action_support, &QAction::triggered, this, &MainWindow::support);
    connect(ui->action_about, &QAction::triggered, this, &MainWindow::about);
    connect(ui->action_doc, &QAction::triggered, this, &MainWindow::doc);
    connect(ui->action_exit, &QAction::triggered, this, &MainWindow::exit);


    connect(ptLoadedData, SIGNAL(removeRowSignal(int)), this, SLOT(removeLoadedDataRow(int)));
    connect(ptStaticticData, SIGNAL(removeRowSignal(int)), this, SLOT(removeStatisticDataRow(int)));
    connect(ptStaticticData, SIGNAL(removeRowSignal(int)), this, SLOT(removeStatisticDataRow(int)));
    connect(ui->pb_build_chart, SIGNAL(clicked()), this, SLOT(buildChart()));

    ptSecondData = new Ptable(ui->frame_table_2);
    chSecondChart = new Chart(ui->frame_second_chart);
    connect(ptSecondData->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(selectSecondDataColumn(int)));
  //  ui->gb_predict->hide();
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

        loadChartSelectors();

        ptSecondData->setHeader(dataMeaning.fieldsHeader());
        ptSecondData->setValues(dataMeaning.loadedMatrix());
   //     ui->cb_load_4->setChecked(true);
    }
}

void MainWindow :: saveStatistic()
{
    qDebug()<<"saveStatistic";
    QString content = dataMeaning.fieldsStatisticHeader().implode(",");
    QVector <Array> values = dataMeaning.statisticMatrix();
    for (int i = 0; i < values.size(); i++) {
        content = content + "\n" + values[i].implode(",");
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("Text (*.txt)"));
    if (fileName.trimmed().right(4) != ".txt") fileName = fileName + ".txt";

    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << (content + "\n");
        file.close();
        QMessageBox::information(this, tr("File is saved"), file.errorString());
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

void MainWindow :: buildChart()
{
    qDebug()<<ui->cb_valuex->currentIndex()<<"\t"<<ui->cb_valuey->currentIndex();
    QVector <QString> header = dataMeaning.fieldsHeader();

    QVector <QString> x = dataMeaning.values(header[ui->cb_valuex->currentIndex()], dataMeaning.isSymbolHeaderField(ui->cb_valuex->currentIndex()));
    QVector <QString> y = dataMeaning.values(header[ui->cb_valuey->currentIndex()], dataMeaning.isSymbolHeaderField(ui->cb_valuey->currentIndex()));

    QVector <QVector <QPair <double, double> > > values(1);
    values[0].resize(x.size());

    for (int i = 0; i < x.size(); i++) {
        values[0][i] = qMakePair(x[i].toDouble(), y[i].toDouble());
    }

    qDebug()<<values;
    this->chChart->createChart(values, ui->cb_plot->currentIndex(), ui->cb_color->currentText(), ui->cb_bcolor->currentText());
}

void MainWindow :: selectSecondDataColumn(int index)
{
    qDebug()<<index;
  //  ui->cb_select_target_4->setChecked(true);
  //  ptSecondData->setDisabled(true);

    QPair <QVector <double>, QVector <QString> > chartValues = dataMeaning.prepareToPredict(index-1);
    qDebug()<<chartValues;
    chSecondChart->createChart(chartValues.first, chartValues.second, dataMeaning.fieldsHeader()[index-1]);
   // ui->gb_predict->show();
  //  ui->frame_table_2->hide();

}

void MainWindow :: loadChartSelectors() {
    QStringList fieldLists;
    QVector <QString> header = dataMeaning.fieldsHeader();
    for (int i = 0; i < header.size(); i++) fieldLists.append(header[i]);
    ui->cb_valuex->clear();
    ui->cb_valuey->clear();

    ui->cb_valuex->addItems(fieldLists);
    ui->cb_valuey->addItems(fieldLists);
}

void MainWindow :: doc()
{
    QUrl url = QUrl::fromLocalFile (QCoreApplication::applicationDirPath() + "/doc.odt");
    bool result = QDesktopServices::openUrl (url);
}

void MainWindow :: about()
{
    About about;
    about.exec();
}

void MainWindow :: support()
{
    Support support;
    support.exec();
}

void MainWindow::exit() {
    QApplication::quit();
}
