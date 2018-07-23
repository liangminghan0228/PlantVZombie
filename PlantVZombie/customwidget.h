#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H


#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = 0);
    ~CustomWidget();

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);
};

#endif // CUSTOMWIDGET_H
