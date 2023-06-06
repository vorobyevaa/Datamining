#include "about.h"
#include "moc/ui_about.h"

About::About(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::About)
{
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}
