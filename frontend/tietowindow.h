#ifndef TIETOWINDOW_H
#define TIETOWINDOW_H

#include <QDialog>

namespace Ui {
class TietoWindow;
}

class TietoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TietoWindow(QWidget *parent = nullptr);
    ~TietoWindow();

private slots:
    void on_btnLoad_clicked();

private:
    Ui::TietoWindow *ui;

};

#endif // TIETOWINDOW_H
