#include "datameaningcore.h"
#include <QtDebug>
#include <QFile>
#include <QCoreApplication>
#include <QIODevice>
#include <QProcess>

DataMeaningCore :: DataMeaningCore()
{   
}

void DataMeaningCore :: callStatisticPy(QVector <DataRow> dataRows, QString header, QString scriptname)
{
    Array bHeader;
    bHeader.push_back(header);
    callStatisticPy(dataRows, bHeader, scriptname);
}

void DataMeaningCore :: callStatisticPy(QVector <DataRow> dataRows, Array header, QString scriptname)
{
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
    QFile file(QCoreApplication::applicationDirPath() + "/"+scriptname+".tmp");
    file.remove();
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << content << endl;
        file.close();
    }

    QStringList outputList = callScript(scriptname, scriptname+".tmp").split("\n\n");

    reportValues.clear();
    for (int i = 0; i < outputList.size(); i++)
    {
        Array rep;
        QStringList sl = outputList[i].split("\n");      
        if (sl.size() <= 1) continue;
        for (int j = 0; j < sl.size(); j++) rep.push_back(sl[j]);     
        reportValues.push_back(rep);
    }
}

QString DataMeaningCore :: callScript(QString scriptname, QString param, QString otherParam, QString thirdParam)
{
    QProcess pingProcess;
    QString exec = "python3";
    QStringList params;
    params.push_back(scriptname + ".py");
    params.push_back(param);
    if (!otherParam.isEmpty())
    {
        params.push_back(otherParam);
    }
    if (!thirdParam.isEmpty())
    {
        params.push_back(thirdParam);
    }
    pingProcess.start(exec, params);    
    pingProcess.waitForFinished();
    QString s = pingProcess.readAllStandardOutput();
    return s;
}

QVector <Array> DataMeaningCore :: report()
{
    return reportValues;
}
