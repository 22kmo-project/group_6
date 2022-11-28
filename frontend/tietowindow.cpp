#include "tietowindow.h"
#include "ui_tietowindow.h"

TietoWindow::TietoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TietoWindow)
{
    ui->setupUi(this);
}

TietoWindow::~TietoWindow()
{
    delete ui;
}

void TietoWindow::on_btnLoad_clicked()
{

}

