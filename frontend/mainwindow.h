#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "asiakaswindow.h"

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QMainWindow>
#include <QTimer>
#include <QScreen>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void loginSlot (QNetworkReply *reply);
    //void on_btnQuit_clicked();
    void lukitusSlot (QNetworkReply *replyLukitus);
    void avausSlot (QNetworkReply *replyAvaus);

    //NUMPAD
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

    void on_btnNP_ok_clicked();
    void on_btnNP_clear_clicked();
    void on_btnNP_stop_clicked();

    void clearData();


private:
    Ui::MainWindow *ui;
    AsiakasWindow *objectAsiakasWindow;
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *lukitusManager;
    QNetworkAccessManager *avausManager;
    QNetworkReply *reply;
    QNetworkReply *replyLukitus;
    QNetworkReply *replyAvaus;
    QByteArray response_data;
    QByteArray token;
    QString id_card;
    int pinCount; //VÄÄRIN ANNETUT PIN-KOODIT
    int cardInserted; //ONKO KORTIN TUNNUS SYÖTETTY 1 = kyllä, 0 = ei
    bool lukitus;


};
#endif // MAINWINDOW_H
