#include "myurl.h"
#include "qnetworkreply.h"
#include "tietowindow.h"
#include "ui_tietowindow.h"

TietoWindow::TietoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TietoWindow)
{
    ui->setupUi(this);
}

TietoWindow::~TietoWindow()
{
    delete ui;
}

void TietoWindow::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}


void TietoWindow::on_btnLoad_clicked()
{

    QString site_url=MyUrl::getBaseUrl()+"/asiakastiedot"; // asiakastiedot jälkeen vielä +my_jotain kunhan tietokannan kautta saadaan toimimaan yhteydet
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    infoManager = new QNetworkAccessManager(this);

    connect(infoManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(infoSlot(QNetworkReply*)));

    reply = infoManager->get(request);
}

void TietoWindow::infoSlot(QNetworkReply *reply)
{
        //response_data=reply->readAll();
        //qDebug()<<response_data;

        QByteArray response_data=reply->readAll();
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonArray json_array = json_doc.array();
        QString info="";
        foreach (const QJsonValue &value, json_array) {
            QJsonObject json_obj = value.toObject();
            info+=("Etunimi: "+json_obj["fname"].toString())+"\n"+
                  ("Sukunimi: "+json_obj["lname"].toString())+"\n"+
                  ("Osoite: "+json_obj["address"].toString())+"\n"+
                  ("Puhelinnumero: "+json_obj["phoneNumber"].toString())+"\r\n";
        }

        qDebug()<<info;

        ui->textInfo->setText(info);

        reply->deleteLater();
        infoManager->deleteLater();
}


void TietoWindow::on_btnBack_clicked()
{
    close();
}

