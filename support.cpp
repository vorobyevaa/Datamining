#include "support.h"
#include "moc/ui_help.h"

Support::Support(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Support)
{
    ui->setupUi(this);
}

Support::~Support()
{
    delete ui;
}
