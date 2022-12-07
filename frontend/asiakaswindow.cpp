#include "asiakaswindow.h"
#include "ui_asiakaswindow.h"
#include "myurl.h"
#include "tietowindow.h"
#include "tilitapahtumat.h"
#include "nosto.h"
#include "saldo.h"
#include "tiedot.h"

AsiakasWindow::AsiakasWindow(QString id_card, QByteArray token, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AsiakasWindow)
{
    ui->setupUi(this);
    myId_card = id_card;
    webToken = token;
    qDebug()<<id_card;
    ui->labelIduser->setAlignment(Qt::AlignCenter);
    QString site_url=MyUrl::getBaseUrl()+"/nimenhaku/"+myId_card;
    QNetworkRequest request((site_url));
    //qDebug()<<site_url;
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    nimiManager = new QNetworkAccessManager(this);

    connect(nimiManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(nimiSlot(QNetworkReply*)));

    reply = nimiManager->get(request);
}

void AsiakasWindow::nimiSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    //qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString nimi="";
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        nimi+=("Tervetuloa käyttämään pankkiautomaattia "+json_obj["fname"].toString())+"\n";
        ui->labelIduser->setText(nimi);
    }
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

void AsiakasWindow::on_btnTiedot_clicked()
{
    ObjectTietoWindow=new TietoWindow(myId_card, webToken);
    ObjectTietoWindow->show();
}

void AsiakasWindow::on_btnLogout_clicked()
{
    this->close();
}



