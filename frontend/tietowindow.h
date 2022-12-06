#ifndef TIETOWINDOW_H
#define TIETOWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QJsonDocument>
#include <QMainWindow>


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
    void on_btnLoad_clicked();
    void infoSlot (QNetworkReply *reply);
    void tiliSlot (QNetworkReply *reply);

    void on_btnBack_clicked();
private:
    Ui::TietoWindow *ui;
    QByteArray webToken;
    QNetworkAccessManager *infoManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString myId_card;
    QNetworkAccessManager *tiliManager;
};

#endif // TIETOWINDOW_H
