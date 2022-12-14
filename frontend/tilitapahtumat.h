#ifndef TILITAPAHTUMAT_H
#define TILITAPAHTUMAT_H
#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QStandardItemModel>
#include <QMainWindow>
#include <QTableWidget>

namespace Ui {
class Tilitapahtumat;
}

class Tilitapahtumat : public QDialog
{
    Q_OBJECT

public:
    explicit Tilitapahtumat(QString id_card,QByteArray token, QWidget *parent = nullptr);
    ~Tilitapahtumat();
    void resetKaikkiAjastimet();

signals:
    void resetAjastin30();

private slots:
    void getTilitapahtumaSlot (QNetworkReply *reply);

    void on_btn_takaisin_clicked();
    void ajastin10Slot();

private:

    int aika10Sek = 0;
    void getTilitapahtuma();
    Ui::Tilitapahtumat *ui;
    QByteArray webToken;
    QNetworkAccessManager *tilitapahtumaManager;
    QString myId_card;
    QNetworkReply *reply;
    QByteArray response_data;
    QTimer * ajastin10;
    QStandardItemModel *model;
    void tableEditor(QJsonDocument);
};

#endif // TILITAPAHTUMAT_H
