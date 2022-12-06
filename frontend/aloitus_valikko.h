#ifndef ALOITUS_VALIKKO_H
#define ALOITUS_VALIKKO_H

#include <QDialog>

namespace Ui {
class Aloitus_valikko;
}

class Aloitus_valikko : public QDialog
{
    Q_OBJECT

public:
    explicit Aloitus_valikko(QWidget *parent = nullptr);
    ~Aloitus_valikko();

private:
    Ui::Aloitus_valikko *ui;
};

#endif // ALOITUS_VALIKKO_H
