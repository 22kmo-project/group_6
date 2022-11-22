#include "asiakaswindow.h"
#include "qdebug.h"
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

const QString &AsiakasWindow::getWebToken() const
{
    return webToken;
}

void AsiakasWindow::setWebToken(const QString &newWebToken)
{
    webToken = newWebToken;
}

void AsiakasWindow::on_btnTiedot_clicked()
{
    QString wb=this->getWebToken();
    qDebug()<<"webtoken="+wb;
}

