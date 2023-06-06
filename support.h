#ifndef SUPPORT_H
#define SUPPORT_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Support; }
QT_END_NAMESPACE

class Support : public QDialog
{
    Q_OBJECT
public:
    Support(QWidget *parent = nullptr);
    ~Support();
private:
    Ui::Support *ui;
};

#endif // SUPPORT_H
