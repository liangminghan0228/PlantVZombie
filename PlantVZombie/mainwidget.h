#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include "customwidget.h"
#include<QMap>
#include<ctime>
#include<QMediaPlayer>
#include<QMediaPlaylist>
namespace Ui {
class MainWidget;
}

class MainWidget : public CustomWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void mousePressEvent(QMouseEvent*event);
    void paintEvent(QPaintEvent *);
    void zombieMove();
    int findZombie(int row);
    QMediaPlayer*player;
protected:
    QMap<int,QPoint>map;
    QMap<int,int>life;
    QMap<int,int>p_life;
    int count;
    QPoint arr[5][9];
    QPoint arr_2[5][19];
    int ifPlant[5][10];
    QTimer*m_timer,*zomb_timer,*ifOver;
    bool flower;
    bool pea;
    int m_nx;
    int m_ny;
    bool ifproduce;
    bool z_time;
signals:
    void gameover(int Case);
private slots:
    void on_btnSeed1_clicked();

    void on_btnSeed2_clicked();
public slots:
    void zombieCome();
    void Over(int Case);
    void checkOver();
protected slots:
    void addsun();
private:
    Ui::MainWidget *ui;
};

#endif
