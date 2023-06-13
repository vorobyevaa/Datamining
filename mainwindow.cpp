#include "mainwindow.h"
#include "about.h"
#include "support.h"
#include "report.h"
#include "ui_mainwindow.h"
#include <QPair>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_createReportFlag(false)
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
    connect(ui->pb_build_chart, SIGNAL(clicked()), this, SLOT(buildChart()));

    ptSecondData = new Ptable(ui->frame_table_2);
    chSecondChart = new Chart(ui->frame_second_chart);
    connect(ptSecondData->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(selectSecondDataColumn(int)));
    connect(ui->pb_start, SIGNAL(clicked()), this, SLOT(buildReport()));

    QLineEdit * calcResultEditX = new QLineEdit(ui->f_result_calc);
    calcResultEditX->setGeometry(200, 25, 125, 25);
    calcResultEditX->show();

    QLabel * calcResultCaptionX = new QLabel(ui->f_result_calc);
    calcResultCaptionX->setGeometry(25, 25, 155, 25);
    calcResultCaptionX->setText("Входное значение");
    calcResultCaptionX->show();

    QLineEdit * calcResultEditY = new QLineEdit(ui->f_result_calc);
    calcResultEditY->setGeometry(200, 75, 125, 25);
    calcResultEditY->show();

    QLabel * calcResultCaptionY = new QLabel(ui->f_result_calc);
    calcResultCaptionY->setGeometry(25, 75, 155, 25);
    calcResultCaptionY->setText("Выходное значение");
    calcResultCaptionY->show();


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
        ui->pb_start->setEnabled(false);
    }
}

void MainWindow :: saveStatistic()
{
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

    QString xcaption = header[ui->cb_valuex->currentIndex()];
    QString ycatpion = header[ui->cb_valuey->currentIndex()];

    QVector <QString> x = dataMeaning.values(xcaption, dataMeaning.isSymbolHeaderField(ui->cb_valuex->currentIndex()));
    QVector <QString> y = dataMeaning.values(ycatpion, dataMeaning.isSymbolHeaderField(ui->cb_valuey->currentIndex()));

    QVector <QVector <QPair <double, double> > > values(1);
    values[0].resize(x.size());

    for (int i = 0; i < x.size(); i++) {
        values[0][i] = qMakePair(x[i].toDouble(), y[i].toDouble());
    }

    this->chChart->setTitle("",qMakePair(xcaption, ycatpion));
    this->chChart->createChart(values, ui->cb_plot->currentIndex(), ui->cb_color->currentText(), ui->cb_bcolor->currentText());
}

void MainWindow :: selectSecondDataColumn(int index)
{
    QPair <QVector <double>, QVector <QString> > chartValues = dataMeaning.prepareToPredict(index-1);
    chSecondChart->createChart(chartValues.first, chartValues.second, dataMeaning.fieldsHeader()[index-1]);
    ui->pb_start->setEnabled(true);
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

void MainWindow :: buildReport()
{
    QObjectList widgetList = ui->gb_predict->children();
    QJsonObject json;
    for (int i = 0; i < widgetList.size(); i++) {
        json.insert(widgetList[i]->objectName(), ((QCheckBox*)widgetList[i])->isChecked());
    }
    QJsonDocument doc(json);
    QString models = QLatin1String(doc.toJson(QJsonDocument::Compact));

    Report report = dataMeaning.createReport(models);
    Array reportKeys = report.keys();

    if (!m_createReportFlag)
    {
        m_reportTabWidgetItems.resize(reportKeys.size());
        QTabWidget * reportTabWidget = new QTabWidget(ui->f_result);
        reportTabWidget->resize(ui->f_result->size());
        for (int i = 0; i < reportKeys.size(); i++)
        {
            m_reportTabWidgetItems[i] = new ReportTabWidgetItem(reportTabWidget, reportKeys[i]);
            m_reportTabWidgetItems[i]->setValues(report.keys(reportKeys[i]), report.values(reportKeys[i]));
        }
        reportTabWidget->show();
        m_createReportFlag = true;
    }
}
