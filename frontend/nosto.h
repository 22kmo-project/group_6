#ifndef NOSTO_H
#define NOSTO_H

#include <QWidget>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QtNetwork>

#include "secondsum.h"

namespace Ui {
class nosto;
}

class nosto : public QWidget
{
    Q_OBJECT

public:
    explicit nosto(QString id_card, QByteArray token, QWidget *parent = nullptr);
    ~nosto();

private slots:
    void on_btnconfirm_clicked();

    void on_btnsum_clicked();

    void on_btnback_clicked();

    void updateBalanceSlot (QNetworkReply *Reply);

    void withdraw(double storeBalance, double amount);

    void balanceSlot (QNetworkReply *Reply);

private:
    Ui::nosto *ui;
    SecondSum *ObjectSecondSum;
    QByteArray webToken;
    QString myId_card;
    QByteArray response_data;
    QNetworkAccessManager *balanceManager;
    QNetworkAccessManager *updateBalanceManager;
    QNetworkReply *reply;
    QString account_balance;
    void getTilitapahtuma();

    double storeBalance;
    double amount;
};

#endif // NOSTO_H
