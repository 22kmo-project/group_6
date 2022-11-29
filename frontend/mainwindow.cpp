#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete objectAsiakasWindow;
    objectAsiakasWindow=nullptr;
}


void MainWindow::on_btnLogin_clicked()
{
    id_card=ui->textIdUser->text();
    QString card_pin=ui->textcard_pin->text();

    QJsonObject jsonObj;
    jsonObj.insert("id_card",id_card);
    jsonObj.insert("card_pin",card_pin);

    QString site_url=MyUrl::getBaseUrl()+"/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());

}

void MainWindow::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    int test=QString::compare(response_data,"false");
    qDebug()<<test;

    if(response_data.length()==0){
        ui->labelInfo->setText("Palvelin ei vastaa");
    }
    else{
        if(QString::compare(response_data,"-4078")==0){
            ui->labelInfo->setText("Virhe tietokantayhteydessä");
        }
        else{
            if(test==0){
                ui->textIdUser->clear();
                ui->textcard_pin->clear();
                ui->labelInfo->setText("Käyttäjätunnus tai salasana ei täsmää");
            }
            else {
                objectAsiakasWindow=new AsiakasWindow(id_card);
                objectAsiakasWindow->setWebToken("Bearer "+response_data);
                objectAsiakasWindow->show();
            }
        }
    }
    reply->deleteLater();
    loginManager->deleteLater();
}

