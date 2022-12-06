#include "tilitapahtumat.h"
#include "ui_tilitapahtumat.h"
#include "myurl.h"
#include "qdebug.h"

Tilitapahtumat::Tilitapahtumat(QString id_card, QByteArray token, QWidget *parent) :
    QDialog(parent),

    ui(new Ui::Tilitapahtumat)
{
    ui->setupUi(this);
    qDebug()<<"Tilitapahtumat konstuktrori ";
    myId_card = id_card;
    webToken = token;
    getTilitapahtuma();

}

Tilitapahtumat::~Tilitapahtumat()
{
    delete ui;

}


void Tilitapahtumat::getTilitapahtuma()
{
    qDebug()<<"Kortti id: "+ myId_card;
    QByteArray myToken="Bearer "+webToken;
    qDebug()<<"Webtoken: "+webToken;
    QString site_url = MyUrl::getBaseUrl() + "/selaa_tilitapahtuma/"+myId_card; //hakee tiedot myId_cardin mukaan
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"),(myToken));


    tilitapahtumaManager = new QNetworkAccessManager(this);

    connect(tilitapahtumaManager, SIGNAL(finished (QNetworkReply*)),this, SLOT(getTilitapahtumaSlot(QNetworkReply*)));

    reply = tilitapahtumaManager->get(request);

}

void Tilitapahtumat::getTilitapahtumaSlot (QNetworkReply *reply)
{

    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString tilitapahtumaInfo;

    tableEditor(json_doc);
    reply->deleteLater();


    qDebug()<< "QString Data: " + tilitapahtumaInfo;
    tilitapahtumaManager->deleteLater();
}

void Tilitapahtumat::tableEditor(QJsonDocument doc)
{
    qDebug()<< doc;

    ui->table_Tilitapahtumat->setColumnCount(4);
    ui->table_Tilitapahtumat->setHorizontalHeaderLabels({"Date", "Time", "Type", "Amount"});

    QTableWidgetItem *date;
        QString dateHolder;
        QStringList splittedDateTime;
        QString timeHolder;
        QTableWidgetItem *time;

        QTableWidgetItem *type;
        QTableWidgetItem *amount;
        QString logString;


        int row=0;
            foreach(const QJsonValue &value, doc.array()){
                ui->table_Tilitapahtumat->insertRow(ui->table_Tilitapahtumat->rowCount());
                QJsonObject json_obj = value.toObject();
                //qDebug()<<json_obj;

                dateHolder = json_obj["date"].toString();  //Tässä otetaan aika
                splittedDateTime = dateHolder.split("T");
                date = new QTableWidgetItem(splittedDateTime[0]);
                timeHolder = splittedDateTime[1].split(".")[0];
                time = new QTableWidgetItem(timeHolder);

                logString = json_obj["transaction"].toString(); // Tässä otetaan tapahtuman tyyppi esim. nosto
                type = new QTableWidgetItem(logString);
                amount = new QTableWidgetItem(QString::number(json_obj["amount"].toInt()) + "€"); // Tässä sitten saadaan määrä

                ui->table_Tilitapahtumat->setItem(row, 0, date);  //asetetaan tauluun columnien arvot riville
                ui->table_Tilitapahtumat->setItem(row, 1, time);
                ui->table_Tilitapahtumat->setItem(row, 2, type);
                ui->table_Tilitapahtumat->setItem(row, 3, amount);
                row++;
            }
            ui->table_Tilitapahtumat->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->table_Tilitapahtumat->resizeRowsToContents();
            ui->table_Tilitapahtumat->scrollToBottom();
            ui->table_Tilitapahtumat->setEditTriggers(QAbstractItemView::NoEditTriggers);
  }

void Tilitapahtumat::on_btn_takaisin_clicked()
    {
        close();
    }
