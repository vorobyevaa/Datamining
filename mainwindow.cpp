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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::importFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text (*.txt *.csv)"));
    qDebug()<<fileName;
        //    if (fileName.trimmed().right(4) != ".txt") fileName = fileName + ".txt";

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
            }
}
