#ifndef NOSTO_H
#define NOSTO_H

#include <QDialog>

namespace Ui {
class Nosto;
}

class Nosto : public QDialog
{
    Q_OBJECT

public:
    explicit Nosto(QWidget *parent = nullptr);
    ~Nosto();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Nosto *ui;

};

#endif // NOSTO_H
