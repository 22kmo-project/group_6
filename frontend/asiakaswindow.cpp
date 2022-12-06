#include "asiakaswindow.h"
#include "ui_asiakaswindow.h"
#include "tietowindow.h"

AsiakasWindow::AsiakasWindow(QString id_card, QByteArray token, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AsiakasWindow)
{
    ui->setupUi(this);
    ui->labelIduser->setText(id_card);
    myId_card=id_card;
    webToken = token;
}

AsiakasWindow::~AsiakasWindow()
{
    delete ui;
    delete ObjectTietoWindow;
    ObjectTietoWindow=nullptr;
}

void AsiakasWindow::on_btnTiedot_clicked()
{
    ObjectTietoWindow=new TietoWindow(myId_card, webToken);
    ObjectTietoWindow->show();
}

