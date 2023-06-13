#include "report.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QtDebug>
#include <QJsonObject>

Report::Report()
{
    m_content = "{'Model': {'Название': ['Первый', 'Второй', 'Третий', 'Четвертый']}}";
    qDebug()<<m_content;
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(m_content.toUtf8(), &error);

    qDebug() << "Error: " << error.errorString() << error.offset << error.error;


    qDebug()<<jsonDocument.isObject();
    qDebug()<<jsonDocument.isArray();
    qDebug()<<jsonDocument.isEmpty();
    qDebug()<<jsonDocument.object().value("Model");
    QJsonArray arrayData =  jsonDocument.array();
qDebug()<<arrayData;

}

