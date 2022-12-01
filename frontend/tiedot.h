#ifndef TIEDOT_H
#define TIEDOT_H

#include <QDialog>

namespace Ui {
class Tiedot;
}

class Tiedot : public QDialog
{
    Q_OBJECT

public:
    explicit Tiedot(QWidget *parent = nullptr);
    ~Tiedot();

private:
    Ui::Tiedot *ui;
};

#endif // TIEDOT_H
