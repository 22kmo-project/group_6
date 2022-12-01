#include "asiakaswindow.h"
#include "qdebug.h"
#include "ui_asiakaswindow.h"
#include "tilitapahtumat.h"
#include "nosto.h"
#include "saldo.h"
#include "tiedot.h"

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

const QString &AsiakasWindow::getWebToken() const
{
    return webToken;
}

void AsiakasWindow::setWebToken(const QString &newWebToken)
{
    webToken = newWebToken;
}




void AsiakasWindow::on_btnTapahtumat_clicked()
{
    Tilitapahtumat tilitapahtumat;
    tilitapahtumat.setModal(true);
    tilitapahtumat.exec();
}

void AsiakasWindow::on_btnNosto_clicked()
{
    Nosto nosto;
    nosto.setModal(true);
    nosto.exec();
}

void AsiakasWindow::on_btnSaldo_clicked()
{
    Saldo saldo;
   saldo.setModal(true);
   saldo.exec();

}

void AsiakasWindow::on_btnTiedot_clicked()
{
    QString wb=this->getWebToken();
    qDebug()<<"webtoken = "+wb;
    Tiedot tietoikkuna;
    tietoikkuna.setModal(true);
    tietoikkuna.exec();


}

void AsiakasWindow::on_btnLogout_clicked()
{
    this->close();
}



