#include "mainwindow.h"
#include "myurl.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pinCount=0;
    cardInserted=0;
    lukitus=false;
    move(QGuiApplication::screens().at(0)->geometry().center() - frameGeometry().center());
    ui->labelInfo->setText("Syötä kortin tunnus ja paina OK");

}

MainWindow::~MainWindow()
{
    delete ui;
    delete objectAsiakasWindow;
}


void MainWindow::on_btnNP_ok_clicked()
{
    cardInserted++;
    if(cardInserted == 1)
    {
        id_card=ui->textIdUser->text();
        ui->textIdUser->clear();
        ui->textIdUser->setEchoMode(QLineEdit::Password);
        ui->labelInfo->setText("Syötä kortin PIN-koodi ja paina OK");
        cardInserted++;
        lukitus=false;
    }
    else
    {
        QString card_pin=ui->textIdUser->text();

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


}


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
                if(pinCount<2)
                {
                ui->textIdUser->clear();
                ui->labelInfo->setText("Kortin tunnus ja PIN-koodi eivät täsmää\ntai kortti on lukittu");
                pinCount++; //väärin annettu pin-koodi +1
                qDebug()<<"pinCount: " << pinCount;

                QJsonObject jsonObj;

                QString site_urlLukitus=MyUrl::getBaseUrl()+"/kortin_lukitus/"+id_card;
                QNetworkRequest request((site_urlLukitus));

                lukitusManager = new QNetworkAccessManager(this);
                connect(lukitusManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(lukitusSlot(QNetworkReply*)));

                replyLukitus = lukitusManager->put(request, QJsonDocument().toJson());

                }
                else
                {
                    ui->textIdUser->clear();
                    ui->labelInfo->setText("PIN-koodi annettu kolme kertaa väärin samalla kortilla\nKortti on nyt varmasti lukittu");
                    qDebug()<<"pinCount: " << pinCount;

                    /*QJsonObject jsonObj;

                    QString site_urlLukitus=MyUrl::getBaseUrl()+"/kortin_lukitus/"+id_card;
                    QNetworkRequest request((site_urlLukitus));

                    lukitusManager = new QNetworkAccessManager(this);
                    connect(lukitusManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(lukitusSlot(QNetworkReply*)));

                    replyLukitus = lukitusManager->put(request, QJsonDocument().toJson());*/
                    pinCount=0;
                }
            }
            else {
                token = "Bearer "+response_data;
                objectAsiakasWindow=new AsiakasWindow(id_card, token);
                objectAsiakasWindow->show();

                cardInserted=0;
                pinCount=0;
                clearData();
                ui->labelInfo->setText("Syötä kortin tunnus ja paina OK");
                ui->textIdUser->setEchoMode(QLineEdit::Normal);
                qDebug()<<pinCount;

                QJsonObject jsonObj;

                QString site_urlAvaus=MyUrl::getBaseUrl()+"/kortin_avaus/"+id_card; //ONNISTUNEEN KIRJAUTUMISEN JÄLKEEN PINKOODIN VÄÄRÄT
                QNetworkRequest request((site_urlAvaus));                           //SYÖTTÖYRITYKSET NOLLATAAN JA KORTTIA (TUNNUSTA) VOI
                                                                                    //KÄYTTÄÄ TAAS NORMAALISTI
                avausManager = new QNetworkAccessManager(this);
                connect(avausManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(avausSlot(QNetworkReply*)));

                replyAvaus = avausManager->put(request, QJsonDocument().toJson());

             


            }
        }
    }
    reply->deleteLater();
    loginManager->deleteLater();
}

void MainWindow::lukitusSlot(QNetworkReply *replyLukitus)
{
    response_data=replyLukitus->readAll();
    qDebug()<<"lukitusSlot"<<response_data;
    int test=QString::compare(response_data, "false");
    qDebug() << test;
}

void MainWindow::avausSlot(QNetworkReply *replyAvaus)
{
    response_data=replyAvaus->readAll();
    qDebug()<<"avausSlot"<<response_data;
    int test=QString::compare(response_data, "false");
    qDebug() << test;
}

/*void MainWindow::on_btnQuit_clicked()
{
    QCoreApplication::quit();
}*/

void MainWindow::on_btnNP_1_clicked()
{
        ui->textIdUser->insert(QString('1'));
}

void MainWindow::on_btnNP_2_clicked()
{
        ui->textIdUser->insert(QString('2'));
}

void MainWindow::on_btnNP_3_clicked()
{
        ui->textIdUser->insert(QString('3'));
}

void MainWindow::on_btnNP_4_clicked()
{
        ui->textIdUser->insert(QString('4'));
}

void MainWindow::on_btnNP_5_clicked()
{
        ui->textIdUser->insert(QString('5'));
}

void MainWindow::on_btnNP_6_clicked()
{
        ui->textIdUser->insert(QString('6'));
}

void MainWindow::on_btnNP_7_clicked()
{
        ui->textIdUser->insert(QString('7'));
}

void MainWindow::on_btnNP_8_clicked()
{
        ui->textIdUser->insert(QString('8'));
}

void MainWindow::on_btnNP_9_clicked()
{
        ui->textIdUser->insert(QString('9'));
}

void MainWindow::on_btnNP_0_clicked()
{
        ui->textIdUser->insert(QString('0'));
}

void MainWindow::on_btnNP_clear_clicked()
{
        ui->textIdUser->clear();
}

void MainWindow::on_btnNP_stop_clicked()
{
        ui->labelInfo->setText("Syötä kortin tunnus ja paina OK");
        ui->textIdUser->setEchoMode(QLineEdit::Normal);
        ui->textIdUser->clear();
        cardInserted=0;
        pinCount=0;
}

void MainWindow::clearData()
{
    ui->textIdUser->clear();
    ui->labelInfo->clear();
}

void MainWindow::clearData()
{
    ui->textIdUser->clear();
    ui->textcard_pin->clear();
    ui->labelInfo->clear();
}

