#include "secondsum.h"
#include "ui_secondsum.h"
#include "myurl.h"
#include "qnetworkreply.h"

#include <QMessageBox>

SecondSum::SecondSum(QString id_card, QByteArray token, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondSum)
{
    ui->setupUi(this);
    webToken=token;
    myId_card=id_card;
    getTilitapahtuma();
}

SecondSum::~SecondSum()
{
    delete ui;
    Amount=0;
}

void SecondSum::on_btnconfirm_clicked()
{
        Amount=ui->nosto_amount->text().toDouble();
        withdraw(storeBalance, Amount);

        if(ui->nosto_amount->text().isEmpty())
        {
            QMessageBox::information(this, "Nosto epäonnistui!", "Kirjoita haluamasi nostosumma.");

}
      {
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

}

void SecondSum::balanceSlot(QNetworkReply *reply)
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

void SecondSum::updateBalanceSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    updateBalanceManager->deleteLater();
}

void SecondSum::withdraw(double storeBalance, double Amount)
{
    if(Amount - storeBalance < 0)
    {
        storeBalance = storeBalance - Amount;
        account_balance = QString::number(storeBalance);

        QMessageBox::information(this, "Nosto onnistui!", "Tililtäsi nostettiin " + ui->nosto_amount->text()+" euroa.");
    }
    else
    {
        QMessageBox::information (this, "Nosto epäonnistui!", "Tilillä ei ole tarpeeksi katetta.");
    }
}

void SecondSum::getTilitapahtuma()
{
QString site_url="http://localhost:3000/tilitiedot/1234";
        QNetworkRequest request((site_url));
        request.setRawHeader(QByteArray("Authorization"),(webToken));
        balanceManager = new QNetworkAccessManager(this);
        connect(balanceManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(balanceSlot(QNetworkReply*)));
        reply = balanceManager->get(request);
}

void SecondSum::on_btncancel_clicked()
{
    this->close();
}
