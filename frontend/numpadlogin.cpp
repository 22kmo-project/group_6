#include "numpadlogin.h"
#include "ui_numpadlogin.h"

NumPadLogin::NumPadLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NumPadLogin)
{
    ui->setupUi(this);
}

NumPadLogin::~NumPadLogin()
{
    delete ui;
}
