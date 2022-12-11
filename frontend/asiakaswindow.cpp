#include "asiakaswindow.h"
#include "ui_asiakaswindow.h"
#include "myurl.h"
#include "tietowindow.h"
#include "tilitapahtumat.h"


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

    ajastin30 = new QTimer;
    connect(ajastin30, SIGNAL(timeout()), this, SLOT(ajastin30Slot()));
    ajastin30->start(1000);
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
    delete ObjectTietoWindow;
    ObjectTilitapahtuma=nullptr;
    ObjectTietoWindow=nullptr;
}


void AsiakasWindow::on_btnTapahtumat_clicked()
{
    ObjectTilitapahtuma=new Tilitapahtumat(myId_card, webToken);
    ObjectTilitapahtuma->show();
    connect(ObjectTilitapahtuma, SIGNAL(resetAjastin30()), this, SLOT(resetAjastimetSlot()));
    resetAjastimetSlot();
}

void AsiakasWindow::on_btnTiedot_clicked()
{
    ObjectTietoWindow=new TietoWindow(myId_card, webToken);
    ObjectTietoWindow->show();
    connect(ObjectTietoWindow, SIGNAL(resetAjastin30()), this, SLOT(resetAjastimetSlot()));
    resetAjastimetSlot();
}

void AsiakasWindow::on_btnLogout_clicked()
{
    logout();
}

void AsiakasWindow::logout()
{
    ajastin30->stop();
    webToken="";
    myId_card="";
    response_data="";
    qDebug()<<"webToken: "<<response_data;
    qDebug()<<"Vai sittenkin: "<<webToken;
    qDebug()<<"id_card: "<<myId_card;
    close();
    delete ajastin30;
}

void AsiakasWindow::ajastin30Slot()
{
    aika30Sek++;
    qDebug()<<" AsiakasWindow 30 timeri: " << aika30Sek << " sekuntia";
    if (aika30Sek > 29)
    {
        logout();
    }
}


void AsiakasWindow::resetAjastimetSlot()
{
       aika30Sek = 0;
}


