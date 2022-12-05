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

}

Tilitapahtumat::~Tilitapahtumat()
{
    delete ui;
}

void Tilitapahtumat::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}
void Tilitapahtumat::setId_card(const QString &newId_card)
{
    id_card = newId_card;
}

void Tilitapahtumat::getTilitapahtumaSlot (QNetworkReply *reply)
{
    //response_data=reply->readAll();
   // qDebug()<<"DATA : "+response_data;
    //qDebug()<<"WEBTOKEN : "+webToken;


    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString tilitapahtumaInfo;


    foreach (const QJsonValue &value, json_array) {
       QJsonObject json_obj = value.toObject();
       tilitapahtumaInfo+=QString::number(json_obj["id_tapahtuma"].toInt())+
                   ", "+json_obj["id_tili"].toString()+
                   ", "+json_obj["date"].toString()+
                   ", "+json_obj["transaction"].toString()+
                   ", "+json_obj["amount"].toDouble()+
                   ", "+json_obj["id_card"].toString()+"\r";


    }
    qDebug()<< "QString Data: " + tilitapahtumaInfo;

    ui->textEdit_2->setText(tilitapahtumaInfo);

 reply->deleteLater();
 tilitapahtumaManager->deleteLater();
}





void Tilitapahtumat::on_btn_getTilitapahtuma_clicked()
{

    qDebug()<<"Kortti id: "+ id_card;
    QString site_url = MyUrl::getBaseUrl() + "/selaa_tilitapahtuma/"+id_card;
    QNetworkRequest request((site_url));


    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    tilitapahtumaManager = new QNetworkAccessManager(this);

    connect(tilitapahtumaManager, SIGNAL(finished (QNetworkReply*)),this, SLOT(getTilitapahtumaSlot(QNetworkReply*)));

    reply = tilitapahtumaManager->get(request);


}

void Tilitapahtumat::on_btn_takaisin_clicked()
    {
        close();
    }
