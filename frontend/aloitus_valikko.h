#ifndef ALOITUS_VALIKKO_H
#define ALOITUS_VALIKKO_H

#include <QDialog>

namespace Ui {
class aloitus_valikko;
}

class aloitus_valikko : public QDialog
{
    Q_OBJECT

public:
    explicit aloitus_valikko(QWidget *parent = nullptr);
    ~aloitus_valikko();

private:
    Ui::aloitus_valikko *ui;
};

#endif // ALOITUS_VALIKKO_H
