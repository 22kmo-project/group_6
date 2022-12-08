#include "mainwindow.h"
#include "myurl.h"
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
}

/*void MainWindow::on_btnLogin_clicked()
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

}*/

void MainWindow::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    int test=QString::compare(response_data,"false");
    qDebug()<<test;

    if(response_data.length()==0)
    {
        ui->labelInfo->setText("Palvelin ei vastaa");
    }
    else{
        if(QString::compare(response_data,"-4078")==0)
        {
            ui->labelInfo->setText("Virhe tietokantayhteydessä");
        }
        else{
            if(test==0)
            {
                ui->textIdUser->clear();
                ui->textcard_pin->clear();
                ui->labelInfo->setText("Käyttäjätunnus tai salasana ei täsmää");
            }
            else {
                token = "Bearer "+response_data;
                objectAsiakasWindow=new AsiakasWindow(id_card, token);
                objectAsiakasWindow->show();
            }
        }
    }
    reply->deleteLater();
    loginManager->deleteLater();
}

void MainWindow::on_btnQuit_clicked()
{
    QCoreApplication::quit();
}

void MainWindow::on_btnNP_1_clicked()
{
    if (ui->textIdUser->text().length() < 10)
    {
        ui->textIdUser->insert(QString('1'));
    }
    else
    {
        ui->textcard_pin->insert(QString('1'));
    }
}

void MainWindow::on_btnNP_2_clicked()
{
    if (ui->textIdUser->text().length() < 10)
    {
        ui->textIdUser->insert(QString('2'));
    }
    else
    {
        ui->textcard_pin->insert(QString('2'));
    }
}

void MainWindow::on_btnNP_3_clicked()
{
    if (ui->textIdUser->text().length() < 10)
    {
        ui->textIdUser->insert(QString('3'));
    }
    else
    {
        ui->textcard_pin->insert(QString('3'));
    }
}

void MainWindow::on_btnNP_4_clicked()
{

    if (ui->textIdUser->text().length() < 10)
    {
        ui->textIdUser->insert(QString('4'));
    }
    else
    {
        ui->textcard_pin->insert(QString('4'));
    }
}

void MainWindow::on_btnNP_5_clicked()
{
    if (ui->textIdUser->text().length() < 10)
    {
        ui->textIdUser->insert(QString('5'));
    }
    else
    {
        ui->textcard_pin->insert(QString('5'));
    }
}

void MainWindow::on_btnNP_6_clicked()
{
    if (ui->textIdUser->text().length() < 10)
    {
        ui->textIdUser->insert(QString('6'));
    }
    else
    {
        ui->textcard_pin->insert(QString('6'));
    }
}

void MainWindow::on_btnNP_7_clicked()
{
    if (ui->textIdUser->text().length() < 10)
    {
        ui->textIdUser->insert(QString('7'));
    }
    else
    {
        ui->textcard_pin->insert(QString('7'));
    }
}

void MainWindow::on_btnNP_8_clicked()
{
    if (ui->textIdUser->text().length() < 10)
    {
        ui->textIdUser->insert(QString('8'));
    }
    else
    {
        ui->textcard_pin->insert(QString('8'));
    }
}

void MainWindow::on_btnNP_9_clicked()
{
    if (ui->textIdUser->text().length() < 10)
    {
        ui->textIdUser->insert(QString('9'));
    }
    else
    {
        ui->textcard_pin->insert(QString('9'));
    }
}

void MainWindow::on_btnNP_0_clicked()
{
    if (ui->textIdUser->text().length() < 10)
    {
        ui->textIdUser->insert(QString('0'));
    }
    else
    {
        ui->textcard_pin->insert(QString('0'));
    }
}

void MainWindow::on_btnNP_ok_clicked()
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

void MainWindow::on_btnNP_clear_clicked()
{
    if (ui->textcard_pin->text().length() > 0)
    {
        ui->textcard_pin->clear();
    }
    else
    {
        ui->textIdUser->clear();
    }
}

void MainWindow::on_btnNP_stop_clicked()
{
        ui->textIdUser->clear();
        ui->textcard_pin->clear();
}

