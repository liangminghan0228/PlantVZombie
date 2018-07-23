#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QPainter>
#include<QMouseEvent>
#include<QPoint>
#include<QDebug>
#include<QTimer>
#include<QImage>
#include<QTime>
#include<QLCDNumber>
#include"overdlg.h"
#include"overdlg2.h"
static int number=0;
static int sum[45]={0};
int pea_arr[45]={0};
int sun_arr[45]={0};
int i,j;
int ifInRect(int x,int y,QPoint point){
    int w,h;
    switch(y){
    case 92:{h=74;if(x==109||x==325||x==396||x==678)w=71;else if(x==180||x==545)w=68;
    else if(x==249||x==468)w=76;else if(x==613)w=65;}break;
    case 166:{h=78;if(x==109||x==325||x==396||x==678)w=71;else if(x==180||x==545)w=68;
        else if(x==249||x==468)w=76;else if(x==613)w=65;}break;
    case 244:{h=84;if(x==109||x==325||x==396||x==678)w=71;else if(x==180||x==545)w=68;
        else if(x==249||x==468)w=76;else if(x==613)w=65;}break;
    case 328:{h=76;if(x==109||x==325||x==396||x==678)w=71;else if(x==180||x==545)w=68;
        else if(x==249||x==468)w=76;else if(x==613)w=65;}break;
    case 404:{h=71;if(x==109||x==325||x==396||x==678)w=71;else if(x==180||x==545)w=68;
        else if(x==249||x==468)w=76;else if(x==613)w=65;}break;
    }
    if(point.x()>x&&point.x()<x+w&&point.y()>y&&point.y()<y+h)return 1;
            else return 0;
}

int whichX(int t){
    if(t>109&&t<=180)return 0;
    else if(t>180&&t<=249)return 1;
    else if(t>249&&t<=325)return 2;
    else if(t>325&&t<=396)return 3;
    else if(t>396&&t<=468)return 4;
    else if(t>468&&t<=545)return 5;
    else if(t>545&&t<=613)return 6;
    else if(t>613&&t<=678)return 7;
    else if(t>678&&t<=797)return 8;
    else return -1;
}

int whichY(int y){
    switch(y){
    case 92:return 0;break;
    case 166:return 1;break;
    case 244:return 2;break;
    case 328:return 3;break;
    case 404:return 4;break;
    }
}

MainWidget::MainWidget(QWidget *parent) :
    CustomWidget(parent),flower(false),pea(false),m_nx(0),m_ny(0),count(0),ifproduce(false),//appear(false),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    player=new QMediaPlayer;
        QMediaPlaylist*playlist=new QMediaPlaylist;
        playlist->addMedia(QUrl::fromLocalFile("D:/QT/qt/PlantVZombie/mp3/bgm2.mp3"));
        // playlist->setCurrentIndex(1);
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        player->setPlaylist(playlist);

        //player->setMedia(QUrl::fromLocalFile(":/mp3/bgm2.mp3"));
        player->play();
    this->setAutoFillBackground(true);
    map[0]=QPoint(0,0);
    m_timer=new QTimer(this);
    zomb_timer=new QTimer(this);
    ifOver=new QTimer(this);
    qsrand(time(NULL));
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/images/bk.png").scaled(this->size())));
    this->setPalette(palette);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(addsun()));
    m_timer->start(12000);
    connect(this,SIGNAL(gameover(int)),this,SLOT(Over(int)));
    connect(zomb_timer,SIGNAL(timeout()),this,SLOT(zombieCome()));
    connect(ifOver,SIGNAL(timeout()),this,SLOT(checkOver()));
    ifOver->start(7000);
     if(number<3)zomb_timer->start(20000-75*number);
     /*else if(number<15)zomb_timer->start(12000);
     else if(number<27)zomb_timer->start(13500);
     else if(number<40)zomb_timer->start(12000);*/
    for(i=0;i<5;i++){
        for(j=0;j<10;j++){
            ifPlant[i][j]=0;
        } }
    for(i=0;i<5;i++){
        arr[i][0].setX(109);arr[i][1].setX(180);arr[i][2].setX(249);arr[i][3].setX(325);arr[i][4].setX(396);
        arr[i][5].setX(468);arr[i][6].setX(545);arr[i][7].setX(613);arr[i][8].setX(678);
    }
    for(j=0;j<9;j++){
        arr[0][j].setY(92);arr[1][j].setY(166);arr[2][j].setY(244);arr[3][j].setY(328);arr[4][j].setY(404);}
    for(j=0;j<45;j++){
        p_life[j]=0;
    }
}

MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::on_btnSeed1_clicked()
{
    flower=!flower;
    pea=false;
}

void MainWidget::on_btnSeed2_clicked()
{
    pea=!pea;
    flower=false;
}


void MainWidget::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        QTimer*timer=new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(update()));
        if(flower==true){
            flower=false;
            if(event->x()>109&&event->x()<751&&
                event->y()>92&&event->y()<477){
            for( i=0;i<5;i++){
                for( j=0;j<9;j++){
                    if(ifInRect(arr[i][j].x(),arr[i][j].y(),event->pos())==1){
                    count=1;break;}
                }
                if(count==1)break;
            }count=0;
            if(ifPlant[i][j]==0&&(ui->NumberOfSun->intValue()>=50)){
            ifPlant[i][j]=1;//种植向日葵
            p_life[9*i+j]=400;
            int temp=ui->NumberOfSun->intValue();
            ui->NumberOfSun->display(temp-50);
            ifproduce=true;
            timer->start(25);
            }
     }}
        else if(pea==true){
            pea=false;
            if(event->x()>109&&event->x()<751&&
                event->y()>92&&event->y()<477){
            for( i=0;i<5;i++){
                for( j=0;j<9;j++){
                    if(ifInRect(arr[i][j].x(),arr[i][j].y(),event->pos())==1)
                    {count=1;break;}
                }if(count==1)break;
            }count=0;
            if(ifPlant[i][j]==0&&(ui->NumberOfSun->intValue()>=100)){
            ifPlant[i][j]=2;//种植豌豆射手
            p_life[9*i+j]=400;//增加生命值
            int temp=ui->NumberOfSun->intValue();
            ui->NumberOfSun->display(temp-100);
            timer->start(25);
            }
        }}
        else {
            for(i=0;i<5;i++){
                for(j=0;j<9;j++){
                    if(ifInRect(arr[i][j].x(),arr[i][j].y(),event->pos())==1&&
                            sun_arr[9*i+j]%100==99){
                        sun_arr[9*i+j]=0;int temp=ui->NumberOfSun->intValue();
                        temp+=25;ui->NumberOfSun->display(temp);count=1;break;
                    }}if(count==1)break;
            }
            count=0;
        }
    }
}

/*void MainWidget::SltUpdatePixmap(){

        this->update();
}*/
void MainWidget::paintEvent(QPaintEvent *){
    QPainter painter(this);
    for(i=1;i<=number;i++){
        if(life.value(i)!=0){
            int m=map.value(i).y();int n=map.value(i).x();
            if(n+80<109)emit gameover(1);
            else if(ifPlant[whichY(m)][whichX(n)]==0)
                zombieMove();
            else if(ifPlant[whichY(m)][whichX(n)]!=0){int temp=p_life[9*whichY(m)+whichX(n)]-25;
                p_life.insert(9*whichY(m)+whichX(n),temp);
                if(p_life[9*whichY(m)+whichX(n)]<=0)ifPlant[whichY(m)][whichX(n)]=0;}
            painter.drawImage(QRect(map.value(i).x(),map.value(i).y()-45,80,116),QImage(":/images/zombie.png"));}
    }
    for(i=0;i<5;i++){
        for(j=0;j<9;j++){
            if(p_life[9*i+j]>=0){
                if(ifPlant[i][j]==1){
                    painter.drawImage(QRect(arr[i][j].x(),arr[i][j].y()-10,80,80),QImage(":/images/sunflower.png"));
                    if(sun_arr[9*i+j]%100!=99)sun_arr[9*i+j]++;
                    else painter.drawImage(QRect(arr[i][j].x()+20,arr[i][j].y()+10,60,60),QImage(":/images/sun.png"));
                }
                else if(ifPlant[i][j]==2){
                    painter.drawImage(QRect(arr[i][j].x(),arr[i][j].y()-10,80,80),QImage(":/images/peashooter.png"));
                    if(ifPlant[i][9]>0){pea_arr[9*i+j]++;int tem=pea_arr[9*i+j]/40+1;int tem_2=findZombie(i);
                        for(int k=1+sum[9*i+j];k<=tem;k++){
                            if(map.value(tem_2).x()>arr[i][j].x()+148+2*pea_arr[9*i+j]-80*k)
                                painter.drawImage(QRect(arr[i][j].x()+70+2*pea_arr[9*i+j]-80*k+78,arr[i][j].y()-10,40,40),
                                                QImage(":/images/pea.png"));
                            else if(map.value(tem_2).x()<=arr[i][j].x()+148+2*pea_arr[9*i+j]-80*k)
                            {sum[9*i+j]++;int l=life[tem_2]-20;life.insert(tem_2,l);if(life[tem_2]<=0)ifPlant[i][9]--;}}}
                }}
    }}
}

void MainWidget::zombieCome(){
    if(number<2){
    number++;
    int rnd=qrand()%5;
    m_ny=arr[rnd][0].y();
    m_nx=751;
    ifPlant[rnd][9]++;
    map[number]=QPoint(m_nx,m_ny);
    life[number]=100;
    QTimer*timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(75);}
}

void MainWidget::zombieMove(){
    int x=map.value(i).x();
    int y=map.value(i).y();
    map.insert(i,QPoint(x-0.003,y));
}

int MainWidget::findZombie(int row){
    int num;
    for(num=1;num<=number;num++){
        if(life.value(num)!=0&&map.value(num).y()==arr[row][0].y())
            break;
    }
    return num;
}

void MainWidget::addsun(){
    int temp=ui->NumberOfSun->intValue();
    ui->NumberOfSun->display(temp+25);
}

void MainWidget::Over(int Case){
    if(Case==1){
       overdlg*ptr=new overdlg;
       ptr->show();
       this->close();
    }
    else if(Case==2){
       overdlg2*p=new overdlg2;
       p->show();
       this->close();
    }
}

void MainWidget::checkOver(){
    if(number==2&&(ifPlant[0][9]+ifPlant[1][9]+ifPlant[2][9]+ifPlant[3][9]+
                    ifPlant[4][9]==0))
        emit gameover(2);
}

//
