#include "tilitapahtumat.h"
#include "ui_tilitapahtumat.h"
#include "myurl.h"
#include "qdebug.h"

Tilitapahtumat::Tilitapahtumat(QWidget *parent) :
    QDialog(parent),

    ui(new Ui::Tilitapahtumat)
{
    ui->setupUi(this);
    qDebug()<<"Tilitapahtumat konstuktrori ";

   /* QString site_url = MyUrl::getBaseUrl() + "/tilitapahtuma";
    QNetworkRequest request((site_url));


    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU

    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished (QNetworkReply*)),this, SLOT(getTilitapahtumaSlot(QNetworkReply*)));

    reply = getManager->get(request);*/


}

Tilitapahtumat::~Tilitapahtumat()
{
    delete ui;
}

void Tilitapahtumat::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void Tilitapahtumat::getTilitapahtumaSlot (QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    qDebug()<<"WEBTOKEN : "+webToken;
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString tilitapahtuma;

    foreach (const QJsonValue &value, json_array) {
       QJsonObject json_obj = value.toObject();
       tilitapahtuma+=QString::number(json_obj["id_tapahtuma"].toInt())+
                   ", "+json_obj["id_tili"].toString()+
                   ", "+json_obj["date"].toString()+
                   ", "+json_obj["transaction"].toString()+
                   ", "+json_obj["amount"].toString()+
                   ", "+json_obj["id_card"].toString();

    qDebug()<< tilitapahtuma;
    ui->textEdit_2->setText(response_data);
    }



 reply->deleteLater();
 getManager->deleteLater();
}


void Tilitapahtumat::on_btn_takaisin_clicked()
{
    close();
}


void Tilitapahtumat::on_btn_getTilitapahtuma_clicked()
{

    QString site_url = MyUrl::getBaseUrl() + "/tilitapahtuma";
    QNetworkRequest request((site_url));


    //WEBTOKEN ALKU

    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished (QNetworkReply*)),this, SLOT(getTilitapahtumaSlot(QNetworkReply*)));

    reply = getManager->get(request);


}

