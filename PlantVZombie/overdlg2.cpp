#include "overdlg2.h"
#include "ui_overdlg2.h"

overdlg2::overdlg2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::overdlg2)
{
    ui->setupUi(this);
}

overdlg2::~overdlg2()
{
    delete ui;
}
