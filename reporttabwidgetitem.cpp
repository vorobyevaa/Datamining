#include "reporttabwidgetitem.h"

ReportTabWidgetItem :: ReportTabWidgetItem(QWidget *parent, QString title) : QTabWidget(parent),  m_ptable(this)
{
    resize(maximumSize());
    ((QTabWidget *)parent)->addTab(this, title);
    show();

    m_ptable.resize(size().width(), size().height());
    m_ptable.setShift(0);
}

void ReportTabWidgetItem :: setValues(Array keys, QVector <Array> values)
{
    Array header(values[0].size());
    m_ptable.setColumnTitles(keys);
    m_ptable.setHeader(header);
    m_ptable.setValues(values);
}
