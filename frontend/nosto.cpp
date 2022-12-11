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
    getTilitapahtuma();
}

nosto::~nosto()
{
    delete ui;
    amount=0;
    delete ObjectSecondSum;
    ObjectSecondSum=nullptr;

}

void nosto::on_btnconfirm_clicked()
{
        if(ui->box400->isChecked()) {
            amount=400;
            withdraw(storeBalance, amount);

        }
        if(ui->box200->isChecked()) {
            amount=200;
            withdraw(storeBalance, amount);

        }
        if(ui->box100->isChecked()) {
            amount=100;
            withdraw(storeBalance, amount);

        }
        if(ui->box60->isChecked()) {
            amount=60;
            withdraw(storeBalance, amount);

        }
        if(ui->box40->isChecked()) {
            amount=40;
            withdraw(storeBalance, amount);

        }
        if (ui->box20->isChecked()) {
            amount=20;
            withdraw(storeBalance, amount);
        }

        QJsonObject jsonObjUpdate;
        jsonObjUpdate.insert("account_balance",account_balance);
        QString site_url=+"http://localhost:3000/tili/1234";
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        request.setRawHeader(QByteArray("Authorization"),(webToken));

        updateBalanceManager = new QNetworkAccessManager(this);
        connect(updateBalanceManager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(updateBalanceSlot(QNetworkReply*)));
        reply = updateBalanceManager->put(request, QJsonDocument(jsonObjUpdate).toJson());

        this->close();
}

void nosto::balanceSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    account_balance=QString::number(json_obj["account_balance"].toDouble());
    storeBalance=QString(account_balance).toDouble();

    qDebug()<<storeBalance;

    reply->deleteLater();
    balanceManager->deleteLater();
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
    if(amount - storeBalance > 0)
    {
        QMessageBox::information (this, "Nosto epäonnistui!", "Tilillä ei ole tarpeeksi katetta.");}

    else if(amount - storeBalance <= 0 && ui->box20->isChecked()){
    storeBalance = storeBalance - amount;
    account_balance = QString::number(storeBalance);
    QMessageBox::information (this, "Nosto onnistui!", "Tililtäsi nostettiin 20 euroa.");}

    else if(amount - storeBalance <= 0 && ui->box40->isChecked()){
    storeBalance = storeBalance - amount;
    account_balance = QString::number(storeBalance);
    QMessageBox::information (this, "Nosto onnistui!", "Tililtäsi nostettiin 40 euroa.");}

    else if(amount - storeBalance <= 0 && ui->box60->isChecked()){
    storeBalance = storeBalance - amount;
    account_balance = QString::number(storeBalance);
    QMessageBox::information (this, "Nosto onnistui!", "Tililtäsi nostettiin 60 euroa.");}

    else if(amount - storeBalance <= 0  && ui->box100->isChecked()){
    storeBalance = storeBalance - amount;
    account_balance = QString::number(storeBalance);
    QMessageBox::information (this, "Nosto onnistui!", "Tililtäsi nostettiin 100 euroa.");}

    else if(amount - storeBalance <= 0 && ui->box200->isChecked()){
    storeBalance = storeBalance - amount;
    account_balance = QString::number(storeBalance);
    QMessageBox::information (this, "Nosto onnistui!", "Tililtäsi nostettiin 200 euroa.");}

    else if(amount - storeBalance <= 0 && ui->box400->isChecked()){
    storeBalance = storeBalance - amount;
    account_balance = QString::number(storeBalance);
    QMessageBox::information (this, "Nosto onnistui!", "Tililtäsi nostettiin 400 euroa.");}

}

void nosto::on_btnsum_clicked()
{
    ObjectSecondSum=new SecondSum(myId_card, webToken);
    ObjectSecondSum->show();
}

void nosto::getTilitapahtuma()
{
    QString site_url="http://localhost:3000/tilitiedot/1234";
            QNetworkRequest request((site_url));
            request.setRawHeader(QByteArray("Authorization"),(webToken));
            balanceManager = new QNetworkAccessManager(this);
            connect(balanceManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(balanceSlot(QNetworkReply*)));
            reply = balanceManager->get(request);
}

void nosto::on_btnback_clicked()
{
    this->close();
}

