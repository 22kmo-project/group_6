#ifndef NUMPADLOGIN_H
#define NUMPADLOGIN_H

#include <QDialog>

namespace Ui {
class NumPadLogin;
}

class NumPadLogin : public QDialog
{
    Q_OBJECT

public:
    explicit NumPadLogin(QWidget *parent = nullptr);
    ~NumPadLogin();

private:
    Ui::NumPadLogin *ui;
};

#endif // NUMPADLOGIN_H
