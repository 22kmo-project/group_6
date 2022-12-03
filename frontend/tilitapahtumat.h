#ifndef TILITAPAHTUMAT_H
#define TILITAPAHTUMAT_H
#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QStandardItemModel>
#include <QMainWindow>

namespace Ui {
class Tilitapahtumat;
}

class Tilitapahtumat : public QDialog
{
    Q_OBJECT

public:
    explicit Tilitapahtumat(QWidget *parent = nullptr);
    ~Tilitapahtumat();

    const QString &getWebToken() const;
    void setWebToken(const QByteArray &newWebToken);

private slots:
    void getTilitapahtumaSlot (QNetworkReply *reply);

    void on_btn_takaisin_clicked();

    void on_btn_getTilitapahtuma_clicked();

private:
    Ui::Tilitapahtumat *ui;
    QByteArray webToken;
    QNetworkAccessManager *getManager;

    QNetworkReply *reply;
    QByteArray response_data;
    QStandardItemModel *model;
};

#endif // TILITAPAHTUMAT_H
