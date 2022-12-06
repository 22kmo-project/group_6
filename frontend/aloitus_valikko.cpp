#include "aloitus_valikko.h"
#include "ui_aloitus_valikko.h"

Aloitus_valikko::Aloitus_valikko(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Aloitus_valikko)
{
    ui->setupUi(this);
}

Aloitus_valikko::~Aloitus_valikko()
{
    delete ui;
}
