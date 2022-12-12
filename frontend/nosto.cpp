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
    amount = 0;

    ajastin4 = new QTimer;
    ajastin10 = new QTimer;
    connect(ajastin10, SIGNAL(timeout()), this, SLOT(ajastin10Slot()));
    connect(ajastin4, SIGNAL(timeout()), this, SLOT(ajastin4Slot()));
    ajastin10->start(1000);
    qDebug()<<"Nosto ikkuna sulkeutuu kun on kulunut 10 sekuntia";

    ui->btnPeruuta->setVisible(false);
    ui->btnconfirm->setVisible(false);
    ui->btnback->setVisible(true);
    ui->btn20->setVisible(true);
    ui->btn40->setVisible(true);
    ui->btn60->setVisible(true);
    ui->btn100->setVisible(true);
    ui->btn200->setVisible(true);
    ui->btn200->setVisible(true);
    ui->labelSumma->setVisible(false);
    ui->label_20->setVisible(true);
    ui->label_40->setVisible(true);
    ui->label_60->setVisible(true);
    ui->label_100->setVisible(true);
    ui->label_200->setVisible(true);
    ui->label_muuSumma->setVisible(true);
    ui->txtNosto->setVisible(true);
    /*ui->btnNP_1->setVisible(false);
    ui->btnNP_2->setVisible(false);
    ui->btnNP_3->setVisible(false);
    ui->btnNP_4->setVisible(false);
    ui->btnNP_5->setVisible(false);
    ui->btnNP_6->setVisible(false);
    ui->btnNP_7->setVisible(false);
    ui->btnNP_8->setVisible(false);
    ui->btnNP_9->setVisible(false);
    ui->btnNP_0->setVisible(false);
    ui->btnNP_ok->setVisible(false);
    ui->btnNP_clear->setVisible(false);
    ui->btnNP_stop->setVisible(false);*/
    ui->widgetNP->setVisible(false);
    ui->lineSumma->setVisible(false);
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
    aika4Sek=0;
    aika10Sek=0;
    emit resetAjastin30();
}

void nosto::on_btn20_clicked()
{
    amountSelected();

    amount=20;

    ui->labelSumma->setText("Haluatko nostaa 20 euroa?");
    qDebug()<<"account_balance: "<< account_balance;
    withdraw(storeBalance, amount);
}

void nosto::on_btn40_clicked()
{
    amountSelected();

    amount=40;

    ui->labelSumma->setText("Haluatko nostaa 40 euroa?");
    qDebug()<<"account_balance: "<< account_balance;
    withdraw(storeBalance, amount);
}

void nosto::on_btn60_clicked()
{
    amountSelected();

    amount=60;

    ui->labelSumma->setText("Haluatko nostaa 60 euroa?");
    qDebug()<<"account_balance: "<< account_balance;
    withdraw(storeBalance, amount);
}

void nosto::on_btn100_clicked()
{
    amountSelected();

    amount=100;

    ui->labelSumma->setText("Haluatko nostaa 100 euroa?");
    qDebug()<<"account_balance: "<< account_balance;
    withdraw(storeBalance, amount);
}

void nosto::on_btn200_clicked()
{
    amountSelected();

    amount=200;

    ui->labelSumma->setText("Haluatko nostaa 200 euroa?");
    qDebug()<<"account_balance: "<< account_balance;
    withdraw(storeBalance, amount);
}

void nosto::on_btnconfirm_clicked()
{
    ui->lineSumma->setVisible(false);
    ui->lineSumma->clear();
    ui->btnconfirm->setVisible(false);
    ui->btnPeruuta->setVisible(false);
    resetKaikkiAjastimet();
    //withdraw(storeBalance, amount);
    qDebug()<<"account_balance: "<< account_balance;
    if (storeBalance - amount >= 0)
    {
    qDebug()<<"ACCOUNT BALANCE: "<<account_balance;
    QJsonObject jsonObjUpdate;

    jsonObjUpdate.insert("account_balance",account_balance);
    QString site_url=MyUrl::getBaseUrl()+"/tili/"+id;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(webToken));

    updateBalanceManager = new QNetworkAccessManager(this);
    connect(updateBalanceManager, SIGNAL(finished(QNetworkReply*)),
    this, SLOT(updateBalanceSlot(QNetworkReply*)));
    reply = updateBalanceManager->put(request, QJsonDocument(jsonObjUpdate).toJson());

    nostoSumma = QString::number(amount);
    ui->labelSumma->setText("Tililtä nostettu "+nostoSumma+" euroa.");
    ajastin4->start(1000);

    createTransaction();
    }
    else
    {
        ui->labelSumma->setText("Tapahtuma hylätty, tilin kate ei riitä.");
        ajastin4->start(1000);
        amount = 0;
    }

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
    }
    //qDebug()<< "10 sek ajastin: " << aika10Sek;
}

void nosto::ajastin4Slot()
{
    aika4Sek++;
    if (aika10Sek > 3)
    {
        ajastin4->stop();
        close();
        delete ajastin4;
    }
    qDebug()<<"ajastin4: "<< aika4Sek;
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
    QString site_url=MyUrl::getBaseUrl()+"/tilitiedot/"+myId_card;
    qDebug()<<"URL: "+site_url;
            QNetworkRequest request((site_url));
            request.setRawHeader(QByteArray("Authorization"),(webToken));
            balanceManager = new QNetworkAccessManager(this);
            connect(balanceManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(balanceSlot(QNetworkReply*)));
            reply = balanceManager->get(request);
}

void nosto::createTransaction()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QDateTime updatedTime = currentTime.addSecs(2 * 60 * 60);
    QString timeString = updatedTime.toString("yyyy-MM-dd hh:mm:ss");

    qDebug() << timeString;
    //luodaan tilitapahtuma
    QJsonObject jsonObjPost;
    jsonObjPost.insert("id_tili", id);
    jsonObjPost.insert("date", timeString);
    jsonObjPost.insert("transaction", "Nosto");
    jsonObjPost.insert("amount", amount);
    jsonObjPost.insert("id_card", myId_card);


    QString site_url=MyUrl::getBaseUrl()+"/tilitapahtuma/";
        QNetworkRequest requestPost((site_url));
        requestPost.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        requestPost.setRawHeader(QByteArray("Authorization"),(webToken));

    createTransactionManager=new QNetworkAccessManager(this);
    connect(createTransactionManager, SIGNAL(finished(QNetworkReply*)),
    this, SLOT(createTransactionSlot(QNetworkReply*)));
    reply = createTransactionManager->post(requestPost, QJsonDocument(jsonObjPost).toJson());
}

void nosto::createTransactionSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    createTransactionManager->deleteLater();
}

void nosto::on_btnback_clicked()
{
    ajastin4->stop();
    ajastin10->stop();
    resetKaikkiAjastimet();
    this->close();
    qDebug()<<ui->lineSumma;
    qDebug()<<amount;
}




void nosto::on_btnPeruuta_clicked()
{
    amount=0;

    resetKaikkiAjastimet();
    ui->btnback->setVisible(true);
    ui->btnPeruuta->setVisible(false);
    ui->btnconfirm->setVisible(false);
    ui->btn20->setVisible(true);
    ui->btn40->setVisible(true);
    ui->btn60->setVisible(true);
    ui->btn100->setVisible(true);
    ui->btn200->setVisible(true);
    ui->btn200->setVisible(true);
    ui->btnMuuSumma->setVisible(true);
    ui->label_20->setVisible(true);
    ui->label_40->setVisible(true);
    ui->label_60->setVisible(true);
    ui->label_100->setVisible(true);
    ui->label_200->setVisible(true);
    ui->label_muuSumma->setVisible(true);
    ui->txtNosto->setVisible(true);

    ui->labelSumma->setVisible(false);

    ui->lineSumma->clear();
    ui->lineSumma->setVisible(false);
}

void nosto::amountSelected()
{
    resetKaikkiAjastimet();
    ui->btnback->setVisible(false);
    ui->btn20->setVisible(false);
    ui->btn40->setVisible(false);
    ui->btn60->setVisible(false);
    ui->btn100->setVisible(false);
    ui->btn200->setVisible(false);
    ui->btn200->setVisible(false);
    ui->btnMuuSumma->setVisible(false);
    ui->label_20->setVisible(false);
    ui->label_40->setVisible(false);
    ui->label_60->setVisible(false);
    ui->label_100->setVisible(false);
    ui->label_200->setVisible(false);
    ui->label_muuSumma->setVisible(false);
    ui->labelSumma->setVisible(true);
    ui->btnconfirm->setVisible(true);
    ui->btnPeruuta->setVisible(true);
    ui->txtNosto->setVisible(false);
}


void nosto::on_btnMuuSumma_clicked()
{
    resetKaikkiAjastimet();
    ui->widgetNP->setVisible(true);

    ui->btnback->setVisible(false);
    ui->btn20->setVisible(false);
    ui->btn40->setVisible(false);
    ui->btn60->setVisible(false);
    ui->btn100->setVisible(false);
    ui->btn200->setVisible(false);
    ui->btn200->setVisible(false);
    ui->btnMuuSumma->setVisible(false);
    ui->label_20->setVisible(false);
    ui->label_40->setVisible(false);
    ui->label_60->setVisible(false);
    ui->label_100->setVisible(false);
    ui->label_200->setVisible(false);
    ui->label_muuSumma->setVisible(false);

    ui->lineSumma->setVisible(true);
}


void nosto::on_btnNP_1_clicked()
{
    resetKaikkiAjastimet();
    ui->lineSumma->insert(QString('1'));
}
void nosto::on_btnNP_2_clicked()
{
    resetKaikkiAjastimet();
    ui->lineSumma->insert(QString('2'));
}
void nosto::on_btnNP_3_clicked()
{
    resetKaikkiAjastimet();
    ui->lineSumma->insert(QString('3'));
}
void nosto::on_btnNP_4_clicked()
{
    resetKaikkiAjastimet();
    ui->lineSumma->insert(QString('4'));
}
void nosto::on_btnNP_5_clicked()
{
    resetKaikkiAjastimet();
    ui->lineSumma->insert(QString('5'));
}
void nosto::on_btnNP_6_clicked()
{
    resetKaikkiAjastimet();
    ui->lineSumma->insert(QString('6'));
}
void nosto::on_btnNP_7_clicked()
{
    resetKaikkiAjastimet();
    ui->lineSumma->insert(QString('7'));
}
void nosto::on_btnNP_8_clicked()
{
    resetKaikkiAjastimet();
    ui->lineSumma->insert(QString('8'));
}
void nosto::on_btnNP_9_clicked()
{
    resetKaikkiAjastimet();
    ui->lineSumma->insert(QString('9'));
}
void nosto::on_btnNP_0_clicked()
{
    resetKaikkiAjastimet();
    ui->lineSumma->insert(QString('0'));
}
void nosto::on_btnNP_stop_clicked()
{
    resetKaikkiAjastimet();
    ui->btnback->setVisible(true);
    ui->btnPeruuta->setVisible(false);
    ui->btnconfirm->setVisible(false);
    ui->btn20->setVisible(true);
    ui->btn40->setVisible(true);
    ui->btn60->setVisible(true);
    ui->btn100->setVisible(true);
    ui->btn200->setVisible(true);
    ui->btn200->setVisible(true);
    ui->btnMuuSumma->setVisible(true);
    ui->label_20->setVisible(true);
    ui->label_40->setVisible(true);
    ui->label_60->setVisible(true);
    ui->label_100->setVisible(true);
    ui->label_200->setVisible(true);
    ui->label_muuSumma->setVisible(true);
    ui->txtNosto->setVisible(true);

    ui->labelSumma->setVisible(false);
    ui->widgetNP->setVisible(false);

    ui->lineSumma->clear();
    ui->lineSumma->setVisible(false);
    qDebug()<<"ajastin4: "<< aika4Sek;
}
void nosto::on_btnNP_clear_clicked()
{
    resetKaikkiAjastimet();
    ui->lineSumma->clear();
    amount = 0;
    qDebug()<<"ajastin4: "<< aika4Sek;
}
void nosto::on_btnNP_ok_clicked()
{
    resetKaikkiAjastimet();

    amountSelected();

    amount=ui->lineSumma->text().toDouble();
    nostoSumma = QString::number(amount);

    ui->labelSumma->setText("Haluatko nostaa "+nostoSumma+" euroa?");
    qDebug()<<"account_balance: "<< account_balance;
    withdraw(storeBalance, amount);

    ui->btnconfirm->setVisible(true);
    ui->btnPeruuta->setVisible(true);
    ui->widgetNP->setVisible(false);
    ui->lineSumma->setVisible(false);
    qDebug()<<"ajastin4: "<< aika4Sek;

}

