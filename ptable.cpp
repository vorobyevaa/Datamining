#include "ptable.h"
#include <QtDebug>
#include <QDir>
#include <QMessageBox>

Ptable :: Ptable(QWidget * owner) : QTableWidget(owner) {
    this->setColumnCount(0);
    this->setRowCount(0);
    this->resize(owner->size());

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // формируем столбцы
    QString captions[] = {"", "", ""};
    for (int i = 0; i < 3; i++) {
        QTableWidgetItem *twiBord = new QTableWidgetItem();
        twiBord->setText(captions[i]);
        this->setHorizontalHeaderItem(i,twiBord);
    }
    setColumnWidth(0, 25);
    setColumnWidth(2, 150);

    // собитие для добавления и удаления
    QObject::connect(this, SIGNAL(cellClicked(int,int)),this,SLOT(sl_cellClicked(int,int)));

    QString imgPath =QDir::currentPath() + "/img/add.jpeg";
    QImage *img = new QImage();
    bool loaded = img->load(imgPath);

    QTableWidgetItem *twiBord = new QTableWidgetItem();
    twiBord->setText("0");
    this->setVerticalHeaderItem(0,twiBord);

        QTableWidgetItem *thumbnail = new QTableWidgetItem;
    //    thumbnail->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(20,20));

        this->setItem(0, 0, thumbnail);

        loaded = img->load(QDir::currentPath() + "/img/gray.jpeg");
       thumbnail = new QTableWidgetItem();
        thumbnail->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(200,30));
     this->setItem(0, 2, thumbnail);

}

void Ptable :: setValues(QVector <Array> values)
{
    this->setRowCount(values.size());
    for (int i = 0; i < values.size(); i++)
    {
         _createRow(i);
        for (int j = 0; j < values[i].size(); j++) {
            QTableWidgetItem * twiJ = new QTableWidgetItem();
            twiJ->setText(values[i][j]);
            this->setItem(i,j+1,twiJ);
        }
    }
}

void Ptable :: setHeader(Array header)
{
    this->setColumnCount(header.size()+1);
    for (int i = 0; i < header.size(); i++) {
        QTableWidgetItem *twiBord = new QTableWidgetItem();
        twiBord->setText(header[i]);
        this->setHorizontalHeaderItem(i+1,twiBord);
    }
}

void Ptable :: _createRow(int rowIndex)
{
    QImage *img = new QImage();
    img->load(QDir::currentPath() + "/img/remove.jpeg");
    QTableWidgetItem *thumbnail = new QTableWidgetItem();
    thumbnail->setData(Qt::DecorationRole, QPixmap::fromImage(*img).scaled(20,20));
    this->setItem(rowIndex, 0, thumbnail);

    QTableWidgetItem *twiBord = new QTableWidgetItem();
    twiBord->setText(QString::number(rowIndex));
    this->setVerticalHeaderItem(rowIndex,twiBord);
}

void Ptable :: sl_cellClicked(int row, int column)
{
    if (column > 0) return;

    if (row > 0) {
        QMessageBox msgBox;
        msgBox.setText("Действительно удалить строку?");
        msgBox.setStandardButtons(QMessageBox::Ok |  QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        if (ret == QMessageBox::Ok) {
            this->removeRow(row);
            for (int i = row; i < this->rowCount(); i++) {
                QTableWidgetItem *twiBord = new QTableWidgetItem();
                twiBord->setText(QString::number(i));
                this->setVerticalHeaderItem(i,twiBord);
            }
            emit removeRowSignal(row);
        }
    }
    else {
        int oldCount = this->rowCount();
        this->insertRow(oldCount);
        this->_createRow(oldCount);
    }

}

bool Ptable :: checkValues(bool showMessageFlag) {
    m_values.clear();
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok);
    double last = this->item(0, 1)->text().toDouble();
    double totalP = 0;
    for (int i = 0; i < rowCount(); i++) {
        QString s = this->item(i, 1)->text().trimmed();
        if (s == "") {
            if (showMessageFlag) {
                msgBox.setText("Границы отрезков не полностью заполнены");
                msgBox.exec();
            }
            return false;
        }
        double bord = this->item(i, 1)->text().toDouble();
        if (bord > last || i == 0) last = bord;
        else {
            if (showMessageFlag) {
                msgBox.setText("Границы отрезков не отсортированы");
                msgBox.exec();
            }
            return false;
        }

        s = this->item(i, 2)->text().trimmed();
        if (s == "" && i > 0) {
            if (showMessageFlag) {
                msgBox.setText("Вероятности не полностью заполнены");
                msgBox.exec();
            }
            return false;
        }
        totalP += this->item(i, 2)->text().toDouble();
        if (i > 0) {
            m_values.push_back(QPair <double, double> (this->item(i, 1)->text().toDouble(),this->item(i, 2)->text().toDouble()));
        }
        else {
            m_a = this->item(i, 1)->text().toDouble();
        }
    }
    if (totalP > 1.0001 || totalP < 0.9999) {
        if (showMessageFlag) {
            msgBox.setText("Общая вероятность получается "+QString::number(totalP)+", а должна быть 1");
            msgBox.exec();
        }
        return false;
    }
    return true;
}

QVector <QVector <double> >  Ptable :: allValues() const
{
    QVector <QVector <double> > result(this->columnCount()-1);
    int rowsCount = this->rowCount()-1;
    for (int i = 0; i < result.size(); i++)
    {
        result[i].resize(rowsCount);
        for (int j = 0; j < result[i].size(); j++)
        {
            result[i][j] = this->item(j+1, i+1)->text().toDouble();
        }
    }
    return result;
}

QVector <QPair <double, double> > Ptable :: values() const
{
    return m_values;
}


QVector <double> Ptable :: p() const
{
    QVector <double> result(m_values.size());
    for (int i = 0; i < m_values.size(); i++) result[i] = m_values[i].second;
    return result;
}

double Ptable :: a() const
{
    return m_a;
}

void Ptable :: rebuildForExperimental(QVector <QString> titles)
{
    this->setColumnCount(titles.size()+1);
    for (int i = 0; i < titles.size(); i++)
    {
        setColumnWidth(i+1, 50);

        QTableWidgetItem *twiBord1 = new QTableWidgetItem();
        twiBord1->setText(titles[i]);
        this->setHorizontalHeaderItem(i+1,twiBord1);
    }
}

void Ptable :: addThirdColumn()
{
    this->setColumnCount(4);
    setColumnWidth(2, 75);
    setColumnWidth(3, 75);
    setSpan(0,2,1,3);
    
    
    QTableWidgetItem *twiBord1 = new QTableWidgetItem();
    twiBord1->setText("заданная");
    this->setHorizontalHeaderItem(2,twiBord1);
        
    QTableWidgetItem *twiBord2 = new QTableWidgetItem();
    twiBord2->setText("факт.");
    this->setHorizontalHeaderItem(3,twiBord2);
}

void Ptable :: setThirdValues(QVector <double> values)
{
    for (int i = 0; i < values.size(); i++)
    {
        QTableWidgetItem * twiJ = new QTableWidgetItem();
        twiJ->setText(QString::number(values[i]));
        this->setItem(i+1,3,twiJ);
    }
}
