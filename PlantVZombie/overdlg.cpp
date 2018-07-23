#include "overdlg.h"
#include "ui_overdlg.h"

overdlg::overdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::overdlg)
{
    ui->setupUi(this);
}

overdlg::~overdlg()
{
    delete ui;
}
