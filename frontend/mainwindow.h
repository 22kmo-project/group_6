#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "asiakaswindow.h"

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QMainWindow>

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
    //void on_btnLogin_clicked();
    void loginSlot (QNetworkReply *reply);
    //void on_btnQuit_clicked();

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

private:
    Ui::MainWindow *ui;
    AsiakasWindow *objectAsiakasWindow;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QByteArray token;
    QString id_card;
};
#endif // MAINWINDOW_H
