#ifndef TILITAPAHTUMAT_H
#define TILITAPAHTUMAT_H
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDialog>

namespace Ui {
class Tilitapahtumat;
}

class Tilitapahtumat : public QDialog
{
    Q_OBJECT

public:
    explicit Tilitapahtumat(QWidget *parent = nullptr);
    ~Tilitapahtumat();


private slots:
    void getTilitapahtumaSlot (QNetworkReply *reply);

private:
    Ui::Tilitapahtumat *ui;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;

};

#endif // TILITAPAHTUMAT_H
