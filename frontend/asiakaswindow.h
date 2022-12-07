#ifndef ASIAKASWINDOW_H
#define ASIAKASWINDOW_H

#include "tietowindow.h"
#include "tilitapahtumat.h"
#include "qdebug.h"

#include <QDialog>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QMainWindow>



namespace Ui {
class AsiakasWindow;
}

class AsiakasWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AsiakasWindow(QString id_card, QByteArray token, QWidget *parent = nullptr);
    ~AsiakasWindow();

private slots:
    void nimiSlot (QNetworkReply *reply);
    void on_btnTiedot_clicked();
    void on_btnTapahtumat_clicked();

    void on_btnLogout_clicked();


private:
    Ui::AsiakasWindow *ui;
    QByteArray webToken;
    TietoWindow *ObjectTietoWindow;
    QString myId_card;
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *nimiManager;
    QNetworkReply *reply;
    QByteArray response_data;
    Tilitapahtumat *ObjectTilitapahtuma;

};

#endif // ASIAKASWINDOW_H
