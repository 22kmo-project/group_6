#include "aloitus_valikko.h"
#include "ui_aloitus_valikko.h"

aloitus_valikko::aloitus_valikko(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aloitus_valikko)
{
    ui->setupUi(this);
}

aloitus_valikko::~aloitus_valikko()
{
    delete ui;
}
