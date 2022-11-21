#include "asiakaswindow.h"
#include "ui_asiakaswindow.h"

AsiakasWindow::AsiakasWindow(QString id_card,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AsiakasWindow)
{
    ui->setupUi(this);
    ui->labelIduser->setText(id_card);
}



AsiakasWindow::~AsiakasWindow()
{
    delete ui;
}
