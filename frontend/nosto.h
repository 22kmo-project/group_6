#ifndef NOSTO_H
#define NOSTO_H

#include <QWidget>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QtNetwork>
#include <string.h>

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

    void createTransaction();
    void createTransactionSlot (QNetworkReply *Reply);

    void withdraw(double storeBalance, double amount);
    void balanceSlot (QNetworkReply *Reply);

    void ajastin10Slot();
    void ajastin4Slot();

    void on_btn20_clicked();
    void on_btn40_clicked();
    void on_btn60_clicked();
    void on_btn100_clicked();
    void on_btn200_clicked();

    void on_btnPeruuta_clicked();

    void amountSelected();

    void on_btnMuuSumma_clicked();

    void on_btnNP_1_clicked();
    void on_btnNP_2_clicked();
    void on_btnNP_3_clicked();
    void on_btnNP_4_clicked();
    void on_btnNP_5_clicked();
    void on_btnNP_6_clicked();
    void on_btnNP_7_clicked();
    void on_btnNP_8_clicked();
    void on_btnNP_9_clicked();
    void on_btnNP_0_clicked();

    void on_btnNP_stop_clicked();
    void on_btnNP_clear_clicked();
    void on_btnNP_ok_clicked();

private:

    int aika4Sek = 0;
    int aika10Sek = 0;
    Ui::nosto *ui;
    SecondSum *ObjectSecondSum;
    QByteArray webToken;
    QString myId_card;
    QByteArray response_data;
    QNetworkAccessManager *balanceManager;
    QNetworkAccessManager *createTransactionManager;
    QNetworkAccessManager *updateBalanceManager;
    QNetworkReply *reply;
    QString account_balance;
    QTimer * ajastin4;
    QTimer * ajastin10;
    QString id;
    QString nostoSumma;

    void getBalance();

    double storeBalance;
    double amount;
    double check;
};

#endif // NOSTO_H
