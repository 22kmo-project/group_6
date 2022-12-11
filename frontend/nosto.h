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
    void resetKaikkiAjastimet();

signals:
    void resetAjastin30();

private slots:

    void on_btnconfirm_clicked();
    void on_btnsum_clicked();

    void on_btnback_clicked();
    void updateBalanceSlot (QNetworkReply *Reply);

    void withdraw(double storeBalance, double amount);
    void balanceSlot (QNetworkReply *Reply);

    void ajastin10Slot();

    void on_btnKaksikymmen_clicked();

    void on_btnPeruuta_clicked();

private:

    int aika10Sek = 0;
    Ui::nosto *ui;
    SecondSum *ObjectSecondSum;
    QByteArray webToken;
    QString myId_card;
    QByteArray response_data;
    QNetworkAccessManager *balanceManager;
    QNetworkAccessManager *updateBalanceManager;
    QNetworkReply *reply;
    QString account_balance;
    QTimer * ajastin10;
    QString id;
    QString nostoSumma;

    void getBalance();

    double storeBalance;
    double amount;
    double check;
};

#endif // NOSTO_H
