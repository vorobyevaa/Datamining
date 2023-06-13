#ifndef REPORTTABWIDGETITEM_H
#define REPORTTABWIDGETITEM_H

#include <QTabWidget>
#include "ptable.h"

class ReportTabWidgetItem : public QTabWidget
{
    Q_OBJECT
public:
    explicit ReportTabWidgetItem(QWidget *parent = nullptr, QString title = "");
    void setValues(Array keys, QVector <Array> values);
private:

    Ptable m_ptable;

signals:

};

#endif // REPORTTABWIDGETITEM_H
