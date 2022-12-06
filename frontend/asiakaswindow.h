#ifndef ASIAKASWINDOW_H
#define ASIAKASWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QMainWindow>
#include "tilitapahtumat.h"
#include "qdebug.h"
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


    void on_btnTapahtumat_clicked();

    void on_btnLogout_clicked();


private:
    Ui::AsiakasWindow *ui;
    QByteArray webToken;
    QString myId_card;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;
    Tilitapahtumat *ObjectTilitapahtuma;

};

#endif // ASIAKASWINDOW_H
