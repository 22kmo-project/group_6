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
    explicit TietoWindow(QWidget *parent = nullptr);
    ~TietoWindow();

    const QString &getWebToken() const;
    void setWebToken(const QByteArray &newWebToken);

private slots:
    void on_btnLoad_clicked();
    void infoSlot (QNetworkReply *reply);

    void on_btnBack_clicked();
private:
    Ui::TietoWindow *ui;
    QByteArray webToken;
    QString myId_card;
    QNetworkAccessManager *infoManager;
    QNetworkReply *reply;
    QByteArray response_data;

};

#endif // TIETOWINDOW_H
