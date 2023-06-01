#include "datameaningcore.h"
#include <QtDebug>
#include <QFile>
#include <QCoreApplication>
#include <QIODevice>
#include "gui/PythonQtScriptingConsole.h"
#include "pythonparameter.h"

DataMeaningCore :: DataMeaningCore()
{
    PythonQt::init(PythonQt::IgnoreSiteModule | PythonQt::RedirectStdOut);
    mainModule = PythonQt::self()->getMainModule();
}

void DataMeaningCore :: callStatisticPy(QVector <DataRow> dataRows, QList <QByteArray> header)
{
    PythonQtScriptingConsole console(NULL, mainModule);
    PythonQt::self()->registerCPPClass("PythonParameter", "","example", PythonQtCreateObject<PythonParameterWrapper>);


    QString content = "";
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

    mainModule.evalFile(QCoreApplication::applicationDirPath() + "/test.py");
}
