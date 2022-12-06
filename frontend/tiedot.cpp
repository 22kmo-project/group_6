#include "tiedot.h"
#include "ui_tiedot.h"

Tiedot::Tiedot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tiedot)
{
    ui->setupUi(this);
}

Tiedot::~Tiedot()
{
    delete ui;
}
