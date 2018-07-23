#ifndef OVERDLG2_H
#define OVERDLG2_H

#include <QDialog>

namespace Ui {
class overdlg2;
}

class overdlg2 : public QDialog
{
    Q_OBJECT

public:
    explicit overdlg2(QWidget *parent = 0);
    ~overdlg2();

private:
    Ui::overdlg2 *ui;
};

#endif // OVERDLG2_H
