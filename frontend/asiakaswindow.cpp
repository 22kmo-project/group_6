#include "asiakaswindow.h"
#include "ui_asiakaswindow.h"
#include "tietowindow.h"

AsiakasWindow::AsiakasWindow(QString id_card,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AsiakasWindow)
{
    ui->setupUi(this);
    ui->labelIduser->setText(id_card);
    myId_card=id_card;
}

AsiakasWindow::~AsiakasWindow()
{
    delete ui;
    delete ObjectTietoWindow;
    ObjectTietoWindow=nullptr;
}

void AsiakasWindow::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void AsiakasWindow::on_btnTiedot_clicked()
{
    ObjectTietoWindow=new TietoWindow();
    ObjectTietoWindow->setWebToken(webToken);
    ObjectTietoWindow->show();
}

