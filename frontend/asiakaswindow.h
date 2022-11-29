#ifndef ASIAKASWINDOW_H
#define ASIAKASWINDOW_H

#include <QDialog>

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
    void setWebToken(const QString &newWebToken);

private slots:
    void on_btnTiedot_clicked();

    void on_btnTapahtumat_clicked();

    void on_btnLogout_clicked();

    void on_btnNosto_clicked();

private:
    Ui::AsiakasWindow *ui;
    QString webToken;
};

#endif // ASIAKASWINDOW_H
