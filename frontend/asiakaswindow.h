#ifndef ASIAKASWINDOW_H
#define ASIAKASWINDOW_H

#include "tietowindow.h"
#include <QDialog>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QMainWindow>


namespace Ui {
class AsiakasWindow;
}

class AsiakasWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AsiakasWindow(QString id_card,QWidget *parent = nullptr);
    ~AsiakasWindow();

    const QString &getWebToken() const;
    void setWebToken(const QByteArray &newWebToken);

private slots:
    void on_btnTiedot_clicked();

private:
    Ui::AsiakasWindow *ui;
    QByteArray webToken;
    QString myId_card;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;
    TietoWindow *ObjectTietoWindow;
};

#endif // ASIAKASWINDOW_H
