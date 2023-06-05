#include "datameaningcore.h"
#include <QtDebug>
#include <QFile>
#include <QCoreApplication>
#include <QIODevice>
//#include "gui/PythonQtScriptingConsole.h"
#include "pythonparameter.h"
#include <QProcess>

DataMeaningCore :: DataMeaningCore()
{
   // PythonQt::init(PythonQt::IgnoreSiteModule | PythonQt::RedirectStdOut);
    //mainModule = PythonQt::self()->getMainModule();
}

void DataMeaningCore :: callStatisticPy(QVector <DataRow> dataRows, QList <QByteArray> header)
{
   // PythonQtScriptingConsole console(NULL, mainModule);
   // PythonQt::self()->registerCPPClass("PythonParameter", "","example", PythonQtCreateObject<PythonParameterWrapper>);


    QString content = "";
    for (int j = 0; j < header.size(); j++)
    {
        if (j > 0) content = content + ",";
        content = content + header[j];
    }
    content = content + "\n";
    for (int i = 0; i < dataRows.size(); i++)
    {
        QString row = "";
        for (int j = 0; j < header.size(); j++)
        {
            if (j > 0) row = row + ",";
            row = row + dataRows[i].value(header[j]);
        }
        content = content + row + "\n";
    }
    QFile file(QCoreApplication::applicationDirPath() + "/statistic.tmp");
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << content << endl;
    }
    file.close();

     QProcess pingProcess;
     QString exec = "python";
     QStringList params;
     params.push_back("statistic.py");
     params.push_back("statistic.tmp");
     pingProcess.start(exec, params);
     pingProcess.waitForFinished(); // sets current thread to sleep and waits for pingProcess end
     QString output(pingProcess.readAllStandardOutput());
     QStringList outputList = output.split("\n\n");

    reportValues.clear();
    for (int i = 0; i < outputList.size(); i++) {
        QVector <QString> rep;
        QStringList sl = outputList[i].split("\n");

      //  qDebug()<<sl.size();
         qDebug()<<sl;
        if (sl.size() <= 1) continue;
        for (int j = 0; j < sl.size(); j++) rep.push_back(sl[j]);
            qDebug()<<rep;
        reportValues.push_back(rep);
    }
    qDebug()<<reportValues;
}


QVector <QVector <QString> > DataMeaningCore :: report()
{
    return reportValues;
}
