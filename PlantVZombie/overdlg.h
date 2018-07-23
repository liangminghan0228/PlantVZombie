#ifndef OVERDLG_H
#define OVERDLG_H

#include <QDialog>

namespace Ui {
class overdlg;
}

class overdlg : public QDialog
{
    Q_OBJECT

public:
    explicit overdlg(QWidget *parent = 0);
    ~overdlg();

private:
    Ui::overdlg *ui;
};

#endif // OVERDLG_H
