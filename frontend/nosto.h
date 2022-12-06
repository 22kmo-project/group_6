#ifndef NOSTO_H
#define NOSTO_H

#include <QWidget>

namespace Ui {
class nosto;
}

class nosto : public QWidget
{
    Q_OBJECT

public:
    explicit nosto(QWidget *parent = nullptr);
    ~nosto();

private slots:
    void on_btnconfirm_clicked();

    void on_btnsum_clicked();

private:
    Ui::nosto *ui;
};

#endif // NOSTO_H
