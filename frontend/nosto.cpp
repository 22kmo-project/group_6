#include "nosto.h"
#include "ui_nosto.h"
#include "secsum.h"

#include <QMessageBox>

nosto::nosto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nosto)
{
    ui->setupUi(this);
}

nosto::~nosto()
{
    delete ui;
}

void nosto::on_btnconfirm_clicked()
{
    if(ui->box400->isChecked () ) {
        QMessageBox::information (this, "Nosto onnistui", "Tililtäsi nostettiin 400");
    }
    if(ui->box200->isChecked () ) {
        QMessageBox::information (this, "Nosto onnistui", "Tililtäsi nostettiin 200");
    }
    if(ui->box100->isChecked () ) {
        QMessageBox::information (this, "Nosto onnistui", "Tililtäsi nostettiin 100");
    }
    if(ui->box60->isChecked () ) {
        QMessageBox::information (this, "Nosto onnistui", "Tililtäsi nostettiin 60");
    }
    if(ui->box40->isChecked () ) {
        QMessageBox::information (this, "Nosto onnistui", "Tililtäsi nostettiin 40");
    }
    if (ui->box20->isChecked () ) {

        QMessageBox::information (this, "Nosto onnistui", "Tilitäsi nostettiin 20");
    }
}


void nosto::on_btnsum_clicked()
{
    SecSum secondSum;
    secondSum.setModal(true);
    secondSum.exec();
}

