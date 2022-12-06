#include "myurl.h"
#include "qnetworkreply.h"
#include "tietowindow.h"
#include "ui_tietowindow.h"

TietoWindow::TietoWindow(QString id_card, QByteArray token, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TietoWindow)
{
    ui->setupUi(this);
    myId_card=id_card;
    ui->btnLoad->hide();
    webToken = token;

    QString site_url=MyUrl::getBaseUrl()+"/asiakastiedot/"+myId_card;
    QNetworkRequest request((site_url));
    //qDebug()<<site_url;
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    infoManager = new QNetworkAccessManager(this);

    connect(infoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(infoSlot(QNetworkReply*)));

    reply = infoManager->get(request);

}

TietoWindow::~TietoWindow()
{
    delete ui;
}


void TietoWindow::on_btnLoad_clicked()
{

}

void TietoWindow::infoSlot(QNetworkReply *reply)
{

        QByteArray response_data=reply->readAll();
        //qDebug()<<response_data;
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonArray json_array = json_doc.array();
        QString info="";
        foreach (const QJsonValue &value, json_array) {
            QJsonObject json_obj = value.toObject();
            info+=("Etunimi: "+json_obj["fname"].toString())+"\n"+
                  ("Sukunimi: "+json_obj["lname"].toString())+"\n"+
                  ("Osoite: "+json_obj["address"].toString())+"\n"+
                  ("Puhelinnumero: "+json_obj["phoneNumber"].toString())+"\r\n";
        ui->textInfo->setText(info);

        QString site_url=MyUrl::getBaseUrl()+"/tilitiedot/"+myId_card;
        QNetworkRequest request((site_url));
        //qDebug()<<site_url;
        //WEBTOKEN ALKU
        request.setRawHeader(QByteArray("Authorization"),(webToken));
        //WEBTOKEN LOPPU
        tiliManager = new QNetworkAccessManager(this);
        connect(tiliManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(tiliSlot(QNetworkReply*)));

        reply = tiliManager->get(request);

        }

        infoManager->deleteLater();
}

void TietoWindow::tiliSlot(QNetworkReply *reply)
{

     QByteArray response_data=reply->readAll();
     //qDebug()<<response_data;
     QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
     QJsonArray json_array = json_doc.array();
     QString tili="";
     foreach (const QJsonValue &value, json_array) {
         QJsonObject json_obj = value.toObject();
         tili+=("Tilin id: "+json_obj["id_tili"].toString())+"\n"+
         "Tilin saldo: "+QString::number(json_obj["account_balance"].toInt())+"€\r\n";

     }
     ui->textTilit->setText(tili);

     reply->deleteLater();
     tiliManager->deleteLater();
}


void TietoWindow::on_btnBack_clicked()
{
    close();
}

