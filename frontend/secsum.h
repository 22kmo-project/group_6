#ifndef SECSUM_H
#define SECSUM_H

#include <QDialog>

namespace Ui {
class SecSum;
}

class SecSum : public QDialog
{
    Q_OBJECT

public:
    explicit SecSum(QWidget *parent = nullptr);
    ~SecSum();

private slots:
    void on_btnconfirm2_clicked();

    void on_btncancel_clicked();

private:
    Ui::SecSum *ui;
};

#endif // SECSUM_H
