#include "customwidget.h"

#include <QStyleOption>
#include <QPainter>


CustomWidget::CustomWidget(QWidget *parent) :
    QWidget(parent)
{

}

CustomWidget::~CustomWidget()
{

}

void CustomWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
