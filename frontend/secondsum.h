#ifndef SECONDSUM_H
#define SECONDSUM_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QMainWindow>
#include <QTimer>

namespace Ui {
class SecondSum;
}

class SecondSum : public QDialog
{
    Q_OBJECT

public:
    explicit SecondSum(QString id_card, QByteArray token, QWidget *parent = nullptr);
    ~SecondSum();
signals:

    void amount(double);

private slots:
    void on_btncancel_clicked();

    void on_btnconfirm_clicked();

    void updateBalanceSlot (QNetworkReply *Reply);

    void withdraw(double storeBalance, double Amount);

    void balanceSlot (QNetworkReply *Reply);
private:
    Ui::SecondSum *ui;
    QByteArray webToken;
    QString myId_card;
    QByteArray response_data;
    QNetworkAccessManager *balanceManager;
    QNetworkAccessManager *updateBalanceManager;
    QNetworkReply *reply;
    QString account_balance;
    void getTilitapahtuma();

    double storeBalance;
    double Amount;
};

#endif // SECONDSUM_H
