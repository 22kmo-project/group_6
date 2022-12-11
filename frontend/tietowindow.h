#ifndef TIETOWINDOW_H
#define TIETOWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QJsonDocument>
#include <QMainWindow>
#include <QTableWidget>
#include <QStandardItemModel>


namespace Ui {
class TietoWindow;
}

class TietoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TietoWindow(QString id_card, QByteArray token, QWidget *parent = nullptr);
    ~TietoWindow();

private slots:
    void infoSlot (QNetworkReply *reply);
    void tiliSlot (QNetworkReply *reply);
    void tapahtumaSlot (QNetworkReply *reply);

    void on_btnBack_clicked();
private:
    void getTapahtuma();
    void tableEditor(QJsonDocument);

    Ui::TietoWindow *ui;

    QNetworkAccessManager *infoManager;
    QNetworkAccessManager *tiliManager;
    QNetworkAccessManager *tapahtumaManager;
    QNetworkReply *reply;

    QStandardItemModel *model;
    QByteArray response_data;
    QByteArray webToken;

    QTimer * ajastin10;
    QString myId_card;
    QString id;
    QString saldo;
};

#endif // TIETOWINDOW_H
