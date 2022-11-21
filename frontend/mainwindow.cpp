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
}


void MainWindow::on_btnLogin_clicked()
{
    id_card=ui->textIdUser->text();
    QString card_pin=ui->textcard_pin->text();

    QJsonObject jsonObj;
    jsonObj.insert("id_card",id_card);
    jsonObj.insert("card_pin",card_pin);

    QString site_url="http://localhost:3000/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());

}

void MainWindow::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;

    /*
    if(id_card.length()==4){
        objectAsiakasWindow=new AsiakasWindow(id_card);
        objectAsiakasWindow->show();
    }
    else {
        ui->textIdUser->clear();
        ui->textcard_pin->clear();
        ui->labelInfo->setText("Käyttäjätunnus tai salasana ei täsmää");
    }*/
}

