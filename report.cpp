#include "report.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QtDebug>
#include <QJsonObject>

Report :: Report()
{
    m_content = "{\'Model\': {\'Название\': [\'Первый\', \'Второй\', \'Третий\', \'Четвертый\'], \'Коэффициент\': [32.63290316753288, -0.0054712594535420555, -0.0008239841009222769, 414.97962513951103], \'Точка пересечения\': [46.2540025861457, 46.2540025861457, 46.2540025861457, 46.2540025861457]}, \'Error\': {\'Mean Absolute Error\': 4.2573263163257025, \'Mean Squared Error:\': 18.75027064341599, \'Root Mean Squared Error:\': 4.330158270019237}}";
   m_content = m_content.replace("'", "\"");
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(m_content.toUtf8(), &error);
    m_value = jsonDocument.object();

    qDebug() << "Error: " << error.errorString() << error.offset << error.error;
}

Array Report :: keys()
{
    return Array(m_value.keys());
}

Array Report :: keys(QString parentKey)
{
    return Array(m_value.value(parentKey).toObject().keys());
}

QVector <Array> Report :: values(QString parentKey)
{
    Array keys = m_value.value(parentKey).toObject().keys();
    QVector <Array> result(keys.size());
    for (int i = 0; i < keys.size(); i++)
    {
        QJsonValue jsonValue = m_value.value(parentKey).toObject().value(keys[i]);
        qDebug()<<"RRRRRR = "<<parentKey<<"\t"<<keys[i]<<"\t"<<jsonValue.isArray()<<"\t"<<jsonValue.isObject()<<"\t"<<jsonValue.isString()<<"\t"<<jsonValue.isDouble();
        if (jsonValue.isDouble())
        {
            result[i].resize(1);
            result[i][0] = QString::number(jsonValue.toDouble());
        }
        else
        {
            QJsonArray jsonArray = m_value.value(parentKey).toObject().value(keys[i]).toArray();
            result[i].resize(jsonArray.size());
            for (int j = 0; j < jsonArray.size(); j++)
            {
                if (jsonArray.at(j).isDouble())
                {
              //      qDebug()<<"d";
                    result[i][j] = QString::number(jsonArray.at(j).toDouble());
                }
                if (jsonArray.at(j).isString())
                {
                 //   qDebug()<<"s";
                    result[i][j] = jsonArray.at(j).toString();
                }
              //  qDebug()<<i<<"\t"<<j<<"\t"<<result[i][j];
              //  qDebug()<<"report "<<i<<"\t"<<j<<"\t"<<jsonArray.at(j).isString()<<"\t"<<jsonArray.at(j)<<" ---- \t"<<jsonArray.at(j).toString()<<" ---- \t"<<jsonArray.at(j).toDouble();
            }
        }
    }
    return result;
}
