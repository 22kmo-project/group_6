#include "nosto.h"
#include "ui_nosto.h"
#include "myurl.h"
#include "qnetworkreply.h"

#include <QMessageBox>

nosto::nosto(QString id_card, QByteArray token, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nosto)
{
    ui->setupUi(this);
    myId_card=id_card;
    webToken=token;
    getBalance();

    ajastin10 = new QTimer;
    connect(ajastin10, SIGNAL(timeout()), this, SLOT(ajastin10Slot()));
    ajastin10->start(1000);
    qDebug()<<"Nosto ikkuna sulkeutuu kun on kulunut 10 sekuntia";

    ui->btnPeruuta->setVisible(false);
    ui->btnconfirm->setVisible(true);
    ui->btnback->setVisible(true);
}

nosto::~nosto()
{
    delete ui;
    amount=0;
    delete ObjectSecondSum;
    ObjectSecondSum=nullptr;
}

void nosto::resetKaikkiAjastimet()
{
    aika10Sek=0;
    emit resetAjastin30();
}

void nosto::on_btnKaksikymmen_clicked()
{
    resetKaikkiAjastimet();
    amount=20;
    ui->btnconfirm->setVisible(true);
    ui->btnPeruuta->setVisible(true);
    ui->labelSumma->setText("Haluatko nostaa 20 euroa?");
    qDebug()<<"account_balance: "<< account_balance;
    withdraw(storeBalance, amount);
}

void nosto::on_btnconfirm_clicked()
{
    resetKaikkiAjastimet();
    //withdraw(storeBalance, amount);
    qDebug()<<"account_balance: "<< account_balance;
    if (storeBalance - amount >= 0)
    {
    qDebug()<<"ACCOUNT BALANCE: "<<account_balance;
    QJsonObject jsonObjUpdate;

    jsonObjUpdate.insert("account_balance",account_balance);
    QString site_url=+"http://localhost:3000/tili/"+id;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(webToken));

    updateBalanceManager = new QNetworkAccessManager(this);
    connect(updateBalanceManager, SIGNAL(finished(QNetworkReply*)),
    this, SLOT(updateBalanceSlot(QNetworkReply*)));
    reply = updateBalanceManager->put(request, QJsonDocument(jsonObjUpdate).toJson());

    ui->labelSumma->setText("Tililtä nostettu 20 euroa.");

    }
    else
    {
        ui->labelSumma->setText("Tapahtuma hylätty, tilin kate ei riitä.");
    }

        /*if (amount == 20)
        {
            resetKaikkiAjastimet();
            withdraw(storeBalance, amount);

            QMessageBox::information (this, "Nosto onnistui!", "Tilitäsi nostettiin 400 euroa.");
        }*/
        /*if(ui->box200->isChecked()) {
            amount=200;
            withdraw(storeBalance, amount);

            QMessageBox::information (this, "Nosto onnistui!", "Tilitäsi nostettiin 200 euroa.");
        }
        if(ui->box100->isChecked()) {
            amount=100;
            withdraw(storeBalance, amount);

            QMessageBox::information (this, "Nosto onnistui!", "Tilitäsi nostettiin 100 euroa.");
        }
        if(ui->box60->isChecked()) {
            amount=60;
            withdraw(storeBalance, amount);

            QMessageBox::information (this, "Nosto onnistui!", "Tilitäsi nostettiin 60 euroa.");
        }
        if(ui->box40->isChecked()) {
            amount=40;
            withdraw(storeBalance, amount);

            QMessageBox::information (this, "Nosto onnistui!", "Tilitäsi nostettiin 40 euroa.");
        }
        if (ui->box20->isChecked()) {
            resetKaikkiAjastimet();
            amount=20;
            withdraw(storeBalance, amount);

            QMessageBox::information (this, "Nosto onnistui!", "Tilitäsi nostettiin 20 euroa.");
        }*/


        //this->close();
}

void nosto::balanceSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    account_balance=QString::number(json_obj["account_balance"].toDouble());
    storeBalance=QString(account_balance).toDouble();
    id=json_obj["id_tili"].toString();

    qDebug()<<storeBalance;
    qDebug()<<"ID TILI: "<<id;

    reply->deleteLater();
    balanceManager->deleteLater();
}


void nosto::ajastin10Slot()
{
    aika10Sek++;
    if (aika10Sek > 9)
    {
        ajastin10->stop();
        close();
        delete ajastin10;
        delete ui;
    }
    //qDebug()<< "10 sek ajastin: " << aika10Sek;
}

void nosto::updateBalanceSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    updateBalanceManager->deleteLater();
}

void nosto::withdraw(double storeBalance, double amount)
{

    storeBalance = storeBalance - amount;
    account_balance = QString::number(storeBalance);
    //account_balance = QString::number(storeBalance);

    qDebug()<<"nostoSumma: "<< nostoSumma;
    qDebug()<<"account_balance: "<< account_balance;
    qDebug()<<"amount: "<< amount;
    qDebug()<<"Store balance: "<< storeBalance;



}

void nosto::on_btnsum_clicked()
{
    resetKaikkiAjastimet();
    ObjectSecondSum=new SecondSum(myId_card, webToken);
    ObjectSecondSum->show();
}

void nosto::getBalance()
{

    QString site_url="http://localhost:3000/tilitiedot/"+myId_card;
            QNetworkRequest request((site_url));
            request.setRawHeader(QByteArray("Authorization"),(webToken));
            balanceManager = new QNetworkAccessManager(this);
            connect(balanceManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(balanceSlot(QNetworkReply*)));
            reply = balanceManager->get(request);

}



void nosto::on_btnback_clicked()
{
    ajastin10->stop();
    resetKaikkiAjastimet();
    this->close();
}




void nosto::on_btnPeruuta_clicked()
{
    resetKaikkiAjastimet();
    ui->btnPeruuta->setVisible(false);
    ui->btnconfirm->setVisible(false);
}

