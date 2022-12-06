#include "secsum.h"
#include "ui_secsum.h"

#include <QMessageBox>

SecSum::SecSum(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecSum)
{
    ui->setupUi(this);
}

SecSum::~SecSum()
{
    delete ui;
}

void SecSum::on_btnconfirm2_clicked()
{
    if(ui->txtedit->text().isEmpty())
    {
        QMessageBox::information(this, "Nosto epäonnistui", "Kirjoita haluamasi nostosumma.");
    }
    else{
        QMessageBox::information(this, "Nosto onnistui", "Tililtäsi nostettiin " + ui->txtedit->text()+" euroa.");
    }
}


void SecSum::on_btncancel_clicked()
{
    this->close();
}

