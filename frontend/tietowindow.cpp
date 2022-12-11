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
    webToken = token;
    getTapahtuma();

    ajastin10 = new QTimer;
    connect(ajastin10, SIGNAL(timeout()), this, SLOT(ajastin10Slot()));
    ajastin10->start(1000);
    qDebug()<<"Tieto ikkuna sulkeutuu kun on kulunut 10 sekuntia";


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
     QJsonObject json_obj = json_doc.object();

     id=json_obj["id_tili"].toString();
     saldo=QString::number(json_obj["account_balance"].toInt());
     QString tiliInfo="Tilin id: "+id+"\r\n"+"Tilin saldo: "+saldo+"€\r\n";

     ui->textTilit->setText(tiliInfo);

     reply->deleteLater();
     tiliManager->deleteLater();
}

void TietoWindow::getTapahtuma()
{
    QString site_url=MyUrl::getBaseUrl()+"/selaa_tilitapahtuma/"+myId_card;
    QNetworkRequest request((site_url));
    //qDebug()<<site_url;
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    tapahtumaManager = new QNetworkAccessManager(this);
    connect(tapahtumaManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(tapahtumaSlot(QNetworkReply*)));

    reply = tapahtumaManager->get(request);
}

void TietoWindow::tapahtumaSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString tapahtumaInfo;

    tableEditor(json_doc);
    reply->deleteLater();


    //qDebug()<< "QString Data: " + tapahtumaInfo;
    tapahtumaManager->deleteLater();
}

void TietoWindow::tableEditor(QJsonDocument doc)
{
    //qDebug()<< doc;
    ui->tableTapahtumat->setRowCount(5);
    ui->tableTapahtumat->setColumnCount(4);
    ui->tableTapahtumat->setHorizontalHeaderLabels({"Date", "Time", "Type", "Amount"});

    QTableWidgetItem *date;
        QString dateHolder;
        QStringList splittedDateTime;
        QString timeHolder;
        QTableWidgetItem *time;

        QTableWidgetItem *type;
        QTableWidgetItem *amount;
        QString logString;
        QString withdraw = "Nosto";

        int row=0;
            foreach(const QJsonValue &value, doc.array()){
                QJsonObject json_obj = value.toObject();
                //qDebug()<<json_obj;

                dateHolder = json_obj["date"].toString();  //Tässä otetaan aika
                splittedDateTime = dateHolder.split("T");
                date = new QTableWidgetItem(splittedDateTime[0]);
                timeHolder = splittedDateTime[1].split(".")[0];
                time = new QTableWidgetItem(timeHolder);

                logString = json_obj["transaction"].toString(); // Tässä otetaan tapahtuman tyyppi esim. nosto
                type = new QTableWidgetItem(logString);
                if(logString==withdraw){  //Tarkistetaan oliko transactionin tyyppi Depit withdraw ja muutetaan määrä negatiiviseksi jos oli
                            amount = new QTableWidgetItem("-" + QString::number(json_obj["amount"].toInt()) + "€" );
                        }else
                            {
                            amount = new QTableWidgetItem(QString::number(json_obj["amount"].toInt()) + "€");
                            }
                ui->tableTapahtumat->setItem(row, 0, date);  //asetetaan tauluun columnien arvot riville
                ui->tableTapahtumat->setItem(row, 1, time);
                ui->tableTapahtumat->setItem(row, 2, type);
                ui->tableTapahtumat->setItem(row, 3, amount);
                row++;
            }
            ui->tableTapahtumat->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableTapahtumat->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableTapahtumat->resizeRowsToContents();
            ui->tableTapahtumat->scrollToBottom();
            ui->tableTapahtumat->setEditTriggers(QAbstractItemView::NoEditTriggers);

  }

void TietoWindow::on_btnBack_clicked()
{
    ajastin10->stop();
    resetKaikkiAjastimet();
    close();
}

void TietoWindow::ajastin10Slot()
{
    aika10Sek++;
    if (aika10Sek > 9)
    {
        ajastin10->stop();
        close();
        delete ajastin10;
        delete ui;
    }
    qDebug()<< "10 sek ajastin: " << aika10Sek;
}

void TietoWindow::resetKaikkiAjastimet()
{
    emit resetAjastin30();
}
