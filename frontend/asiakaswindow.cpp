#include "asiakaswindow.h"

#include "ui_asiakaswindow.h"
#include "tilitapahtumat.h"
#include "nosto.h"
#include "saldo.h"
#include "tiedot.h"

AsiakasWindow::AsiakasWindow(QString id_card, QByteArray token, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AsiakasWindow)
{
    ui->setupUi(this);
    ui->labelIduser->setText(id_card);
    myId_card = id_card;
    webToken = token;
    qDebug()<<id_card;
}



AsiakasWindow::~AsiakasWindow()
{
    delete ui;
    delete ObjectTilitapahtuma;
    ObjectTilitapahtuma=nullptr;
}


void AsiakasWindow::on_btnTapahtumat_clicked()
{
    ObjectTilitapahtuma = new Tilitapahtumat(myId_card, webToken);
    ObjectTilitapahtuma -> show();
}


void AsiakasWindow::on_btnLogout_clicked()
{
    this->close();
}



