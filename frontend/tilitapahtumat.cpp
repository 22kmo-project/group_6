#include "tilitapahtumat.h"
#include "ui_tilitapahtumat.h"

#include "qdebug.h"

Tilitapahtumat::Tilitapahtumat(QWidget *parent) :
    QDialog(parent),

    ui(new Ui::Tilitapahtumat)
{
    ui->setupUi(this);
    qDebug()<<"Tilitapahtumat konstuktrori ";

    QString site_url="http://localhost:3000/tilitapahtuma";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished (QNetworkReply*)),this, SLOT(getTilitapahtumaSlot(QNetworkReply*)));
    reply = getManager->get(request);


}

Tilitapahtumat::~Tilitapahtumat()
{
    delete ui;
}

void Tilitapahtumat::getTilitapahtumaSlot (QNetworkReply *reply)
{
 response_data=reply->readAll();
 qDebug()<<"DATA : "+response_data;
 QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
 QJsonArray json_array = json_doc.array();
 QString tilitapahtuma;
 foreach (const QJsonValue &value, json_array) {
    QJsonObject json_obj = value.toObject();
    tilitapahtuma+=QString::number(json_obj["id_tapahtuma"].toInt())+", "+json_obj["id_tili"].toString()+
            ", "+json_obj["date"].toString()+
            ", "+json_obj["transaction"].toString()+
            ", "+json_obj["amount"].toString()+
            ", "+json_obj["id_card"].toString();

  //ui->tableView_Tilitapa->setModel(tilitapahtuma);
    ui->textEdit_2->setText(tilitapahtuma);
 }



 reply->deleteLater();
 getManager->deleteLater();
}

