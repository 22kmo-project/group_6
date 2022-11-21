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

private:
    Ui::AsiakasWindow *ui;
};

#endif // ASIAKASWINDOW_H
