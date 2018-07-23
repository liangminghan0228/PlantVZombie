#include "loadwidget.h"
#include "ui_loadwidget.h"
#include "mainwidget.h"

#include <QPainter>
#include <QPixmap>

#include <QTimer>

#include <QDebug>

LoadWidget::LoadWidget(QWidget *parent) :
    CustomWidget(parent),
    ui(new Ui::LoadWidget)
{
    ui->setupUi(this);
    ui->btnStart->setVisible(false);

    connect(ui->widgetGrass, SIGNAL(signalFinished()), this, SLOT(SltLoadFinished()));
    connect(ui->btnStart, SIGNAL(clicked(bool)), this, SLOT(SltStartGame()));
    player=new QMediaPlayer;
        QMediaPlaylist*playlist=new QMediaPlaylist;
        playlist->addMedia(QUrl::fromLocalFile("D:/QT/qt/PlantVZombie/mp3/bgm1.mp3"));
      
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        player->setPlaylist(playlist);
    
        
        player->play();
}

LoadWidget::~LoadWidget()
{
    delete ui;
}

void LoadWidget::SltLoadFinished()
{
    ui->btnStart->setVisible(true);
}

// 开始
void LoadWidget::SltStartGame()
{
    MainWidget *mainwWidget = new MainWidget();
    mainwWidget->show();
player->stop();
    this->close();
}


//////////////////////////////////////////////////
/// \brief WidgetGrass::paintEvent
///
WidgetGrass::WidgetGrass(QWidget *parent) :
    CustomWidget(parent)
{
    pixmapWood = QPixmap(":/images/wood.png");
    pixmapGrass = QPixmap(":/images/grass.png");
    pixmapCircle = QPixmap(":/images/circle.png");
    this->setFixedSize(260, 84);

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(50);
}

WidgetGrass::~WidgetGrass()
{

}

void WidgetGrass::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    static int nStep   = 10;

    // 先绘制底部背景图片
    painter.drawPixmap(0, this->height() - 40, pixmapWood);
    painter.drawPixmap(0, this->height() - 80,  pixmapGrass.copy(0, 0, nStep, 48));
    if (nStep < 250) painter.drawPixmap(nStep - 10, 0,  pixmapCircle.scaled(50, 50));

    nStep += 1;
    if (nStep  >= 260) {
        m_timer->stop();
        Q_EMIT signalFinished();
    }
}
