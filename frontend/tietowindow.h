#ifndef TIETOWINDOW_H
#define TIETOWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QJsonDocument>
#include <QMainWindow>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QDebug>


namespace Ui {
class TietoWindow;
}

class TietoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TietoWindow(QString id_card, QByteArray token, QWidget *parent = nullptr);
    ~TietoWindow();
    void resetKaikkiAjastimet();

signals:
    void resetAjastin30();

private slots:
    void infoSlot (QNetworkReply *reply);
    void tiliSlot (QNetworkReply *reply);
    void tapahtumaSlot (QNetworkReply *reply);

    void on_btnBack_clicked();
    void ajastin10Slot();
private:

    int aika10Sek = 0;
    void getTapahtuma();
    Ui::TietoWindow *ui;
    QByteArray webToken;
    QNetworkAccessManager *infoManager;
    QNetworkAccessManager *tiliManager;
    QNetworkAccessManager *tapahtumaManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QTimer * ajastin30;
    QTimer * ajastin10;
    QString myId_card;
    QStandardItemModel *model;
    void tableEditor(QJsonDocument);

};

#endif // TIETOWINDOW_H
