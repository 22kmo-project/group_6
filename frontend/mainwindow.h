#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "asiakaswindow.h"
#include "myurl.h"

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
    void on_btnLogin_clicked();
    void loginSlot (QNetworkReply *reply);

    void on_btnQuit_clicked();

private:
    Ui::MainWindow *ui;
    AsiakasWindow *objectAsiakasWindow;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString id_card;

};
#endif // MAINWINDOW_H
