#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "enemy.h"
#include "defend_tower.h"
#include "waypoint.h"
#include "auxiliary_function.h"
#include "selectbutton.h"
#include "selectbutton2.h"
#include "start.h"

#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QPushButton>
#include <QDebug>
#include <QPoint>
#include <QTimer>
#include <QString>

static const int tower1Cost=300;//第一种塔的价钱（具体再根据情况调整）
static const int tower2Cost=400;//第二种
static const int tower3Cost=500;//第三种

static const int towerupdate1Cost=300;//塔第一次升级的价钱
static const int towerupdate2Cost=400;//第二次升级


MainWindow::MainWindow(int lev,QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    level(lev),
    m_waves(0),
    m_gameWin(0),
    m_gameLose(0),
    m_playerHp(0),
    m_playerGold(0)
{
    this->setFixedSize(750,375);
    ui->setupUi(this);
    this->resize(QSize(800,500));//为什么要这句

    QTimer * timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateMap()));
    timer->start(30);
    //可以通过修改第一个参数来改变游戏开始时间，预留出建塔的时间
    QTimer::singleShot(3000,this,SLOT(gameStart()));

    if(level==1)loadTowerPosition1();
    else if(level==2)loadTowerPosition2();
    else if(level==3)loadTowerPosition3();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::gameStart()
{
    loadWaves();
}

void MainWindow::updateMap()
{
    foreach(Enemy * enemy,m_enemyList)
        enemy->move();
    foreach(Defend_Tower * tower,m_towerList)
        tower->checkEnemyInRange();
    update();
}


void MainWindow::paintEvent(QPaintEvent* )
{
    QPainter painter(this);

    if(m_gameLose||m_gameWin)
    {
        QString text= m_gameWin ? "You Lost":"You win";//这里最后还是改成贴图吧
        painter.setPen(Qt::red);
        painter.drawText(rect(),Qt::AlignCenter,text);
        return;
        //彩蛋也可以在这里添加，比如开一个计时器，button，如果点击看视频或者图片就可以复活
    }

    painter.drawPixmap(0,0,this->width(),this->height(),getpath());
    if(level==1||level==2)
    {
        foreach(const wayPoint * waypoint, m_wayPointList)
           waypoint->draw(&painter);
    }
    else if(level==3)//第三关有三条航线
    {
        foreach(const wayPoint * waypoint, m_wayPointList)
           waypoint->draw(&painter);
        foreach(const wayPoint * waypoint, m_wayPointList1)
           waypoint->draw(&painter);
        foreach(const wayPoint * waypoint, m_wayPointList2)
           waypoint->draw(&painter);
    }


    foreach(const TowerPosition towerposition,m_towerPositionList)
    {
        if(!towerposition.m_hasTower){
            towerposition.draw(&painter);//把hastower改成了公有成员，这样可以在类外使用，实现了有防御塔时防御塔坑的隐藏
        }
    }

    foreach(const Defend_Tower * tower,m_towerList)
        tower->draw(&painter);

    foreach(const wayPoint * waypoint,m_wayPointList)
        waypoint->draw(&painter);

    foreach(const Enemy * enemy,m_enemyList)
        enemy->draw(&painter);

    foreach(const Bullet * bullet,m_bulletList)//这里特殊子弹类是不是还要再加一组语句
        bullet->draw(&painter);

    foreach(const selectButton * button,m_selectButtonList)
        button->draw(&painter);

    foreach(const selectButton2 * button2,m_selectButton2List)
        button2->draw(&painter);

    drawHp(&painter);
    drawGold(&painter);
    drawWaves(&painter);

}

QString MainWindow::getpath()
{
    return nowpath;
}

void MainWindow::setpath(QString path)
{
    nowpath=path;
}

void MainWindow::addWayPoint1()
{
    wayPoint * waypoint1=new wayPoint(QPoint(215,6));
    m_wayPointList.push_back(waypoint1);

    wayPoint * waypoint2=new wayPoint(QPoint(215,140));
    waypoint1->setNextWayPoint(waypoint2);
    m_wayPointList.push_back(waypoint2);

    wayPoint * waypoint3=new wayPoint(QPoint(340,140));
    waypoint2->setNextWayPoint(waypoint3);
    m_wayPointList.push_back(waypoint3);

    wayPoint * waypoint4=new wayPoint(QPoint(340,205));
    waypoint3->setNextWayPoint(waypoint4);
    m_wayPointList.push_back(waypoint4);

    wayPoint * waypoint5=new wayPoint(QPoint(440,205));
    waypoint4->setNextWayPoint(waypoint5);
    m_wayPointList.push_back(waypoint5);

    wayPoint * waypoint6=new wayPoint(QPoint(440,265));
    waypoint5->setNextWayPoint(waypoint6);
    m_wayPointList.push_back(waypoint6);

    wayPoint * waypoint7=new wayPoint(QPoint(390,265));
    waypoint6->setNextWayPoint(waypoint7);
    m_wayPointList.push_back(waypoint7);

    wayPoint * waypoint8=new wayPoint(QPoint(390,430));
    waypoint7->setNextWayPoint(waypoint8);
    m_wayPointList.push_back(waypoint8);

    wayPoint * waypoint9=new wayPoint(QPoint(700,430));
    waypoint8->setNextWayPoint(waypoint9);
    m_wayPointList.push_back(waypoint9);
}


void MainWindow::addWayPoint2()
{
    wayPoint * waypoint1=new wayPoint(QPoint(190,490));
    m_wayPointList.push_back(waypoint1);

    wayPoint * waypoint2=new wayPoint(QPoint(190,390));
    waypoint1->setNextWayPoint(waypoint2);
    m_wayPointList.push_back(waypoint2);

    wayPoint * waypoint3=new wayPoint(QPoint(410,390));
    waypoint2->setNextWayPoint(waypoint3);
    m_wayPointList.push_back(waypoint3);

    wayPoint * waypoint4=new wayPoint(QPoint(410,300));
    waypoint3->setNextWayPoint(waypoint4);
    m_wayPointList.push_back(waypoint4);

    wayPoint * waypoint5=new wayPoint(QPoint(265,300));
    waypoint4->setNextWayPoint(waypoint5);
    m_wayPointList.push_back(waypoint5);

    wayPoint * waypoint6=new wayPoint(QPoint(265,205));
    waypoint5->setNextWayPoint(waypoint6);
    m_wayPointList.push_back(waypoint6);

    wayPoint * waypoint7=new wayPoint(QPoint(510,205));
    waypoint6->setNextWayPoint(waypoint7);
    m_wayPointList.push_back(waypoint7);

    wayPoint * waypoint8=new wayPoint(QPoint(510,300));
    waypoint7->setNextWayPoint(waypoint8);
    m_wayPointList.push_back(waypoint8);

    wayPoint * waypoint9=new wayPoint(QPoint(640,300));
    waypoint8->setNextWayPoint(waypoint9);
    m_wayPointList.push_back(waypoint9);

    wayPoint * waypoint10=new wayPoint(QPoint(640,195));
    waypoint9->setNextWayPoint(waypoint10);
    m_wayPointList.push_back(waypoint10);
}

void MainWindow::addWayPoint3()
{
    wayPoint * waypoint1x=new wayPoint(QPoint(15,230));
    wayPoint * waypoint1y=new wayPoint(QPoint(15,230));
    wayPoint * waypoint1z=new wayPoint(QPoint(15,230));
    m_wayPointList.push_back(waypoint1x);
    m_wayPointList1.push_back(waypoint1y);
    m_wayPointList2.push_back(waypoint1z);


    wayPoint * waypoint2x=new wayPoint(QPoint(160,230));
    wayPoint * waypoint2y=new wayPoint(QPoint(160,230));
    wayPoint * waypoint2z=new wayPoint(QPoint(160,230));
    waypoint1x->setNextWayPoint(waypoint2x);
    waypoint1y->setNextWayPoint(waypoint2y);
    waypoint1z->setNextWayPoint(waypoint2z);
    m_wayPointList.push_back(waypoint2x);
    m_wayPointList1.push_back(waypoint2y);
    m_wayPointList2.push_back(waypoint2z);


    wayPoint * waypoint3x=new wayPoint(QPoint(160,130));
    waypoint2x->setNextWayPoint(waypoint3x);
    m_wayPointList.push_back(waypoint3x);

    wayPoint * waypoint3y=new wayPoint(QPoint(160,330));
    waypoint2y->setNextWayPoint(waypoint3y);
    m_wayPointList.push_back(waypoint3y);

    wayPoint * waypoint3z=new wayPoint(QPoint(160,330));
    waypoint2z->setNextWayPoint(waypoint3z);
    m_wayPointList.push_back(waypoint3z);



    wayPoint * waypoint4x=new wayPoint(QPoint(290,130));
    waypoint3x->setNextWayPoint(waypoint4x);
    m_wayPointList.push_back(waypoint4x);

    wayPoint * waypoint4y=new wayPoint(QPoint(270,330));
    waypoint3y->setNextWayPoint(waypoint4y);
    m_wayPointList.push_back(waypoint4y);

    wayPoint * waypoint4z=new wayPoint(QPoint(270,330));
    waypoint3z->setNextWayPoint(waypoint4z);
    m_wayPointList.push_back(waypoint4z);



    wayPoint * waypoint5x=new wayPoint(QPoint(290,80));
    waypoint4x->setNextWayPoint(waypoint5x);
    m_wayPointList.push_back(waypoint5x);

    wayPoint * waypoint5y=new wayPoint(QPoint(300,260));
    waypoint4y->setNextWayPoint(waypoint5y);
    m_wayPointList.push_back(waypoint5y);

    wayPoint * waypoint5z=new wayPoint(QPoint(270,415));
    waypoint4z->setNextWayPoint(waypoint5z);
    m_wayPointList.push_back(waypoint5z);



    wayPoint * waypoint6x=new wayPoint(QPoint(570,80));
    waypoint5x->setNextWayPoint(waypoint6x);
    m_wayPointList.push_back(waypoint6x);

    wayPoint * waypoint6y=new wayPoint(QPoint(690,260));
    waypoint5y->setNextWayPoint(waypoint6y);
    m_wayPointList.push_back(waypoint6y);

    wayPoint * waypoint6z=new wayPoint(QPoint(690,415));
    waypoint5z->setNextWayPoint(waypoint6z);
    m_wayPointList.push_back(waypoint6z);


    wayPoint * waypoint7x=new wayPoint(QPoint(570,135));
    waypoint6x->setNextWayPoint(waypoint7x);
    m_wayPointList.push_back(waypoint7x);



    wayPoint * waypoint8=new wayPoint(QPoint(730,135));
    waypoint7x->setNextWayPoint(waypoint8);
    m_wayPointList.push_back(waypoint8);

    waypoint6y->setNextWayPoint(waypoint8);
    m_wayPointList1.push_back(waypoint8);

    waypoint6z->setNextWayPoint(waypoint6y);
    m_wayPointList2.push_back(waypoint6y);
    m_wayPointList2.push_back(waypoint8);

}

void MainWindow::loadTowerPosition1()
{
    QPoint pos[]=
    {
        QPoint(290,170),
        QPoint(365,145),
        QPoint(390,220),
        QPoint(465,220),
        QPoint(410,285),
        QPoint(410,370),
        QPoint(550,440),

    };
    int number=sizeof(pos)/sizeof(pos[0]);
    for(int i=0;i<number;i++)
    {
        m_towerPositionList.push_back(pos[i]);
    }
}

void MainWindow::loadTowerPosition2()
{
    QPoint pos[]=
    {
        QPoint(240,335),
        QPoint(350,320),
        QPoint(290,240),
        QPoint(370,240),
        QPoint(455,240),
        QPoint(555,240),
        QPoint(290,155),


    };
    int number=sizeof(pos)/sizeof(pos[0]);
    for(int i=0;i<number;i++)
    {
        m_towerPositionList.push_back(pos[i]);
    }
}

void MainWindow::loadTowerPosition3()
{
    QPoint pos[]=
    {
        QPoint(90,250),

        QPoint(200,210),
        QPoint(200,345),

        QPoint(350,170),
        QPoint(465,170),
        QPoint(570,170),

        QPoint(350,100),
        QPoint(465,100),

        QPoint(410,285),
        QPoint(525,285),
        QPoint(620,285),

        QPoint(350,440),
        QPoint(465,440),
        QPoint(595,440),

        QPoint(640,70),
        QPoint(710,240),
        QPoint(220,60)

    };
    int number=sizeof(pos)/sizeof(pos[0]);
    for(int i=0;i<number;i++)
    {
        m_towerPositionList.push_back(pos[i]);
    }
}

bool MainWindow::canBuyTower(int i)
{//依据具体金额再做修改
    switch (i)
    {
    case 1:
        if(m_playerGold>=400) return true; break;
    case 2:
        if(m_playerGold>=500) return true; break;
    case 3:
        if(m_playerGold>=600) return true; break;
    }
    return false;
}

void MainWindow::removeTower(Defend_Tower *tower)
{
    Q_ASSERT(tower);
    m_towerList.removeOne(tower);
    delete tower;
}

void MainWindow::removeEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);
    m_enemyList.removeOne(enemy);
    delete enemy;
    if(m_enemyList.empty())
    {
        ++m_waves;
        if(!loadWaves())
        {
            m_gameWin=true;
        }
    }
}

void MainWindow::removeButton(selectButton *button)
{
    Q_ASSERT(button);
    m_selectButtonList.removeOne(button);
    delete button;
}

void MainWindow::removeButton2(selectButton2 *button)
{
    Q_ASSERT(button);
    m_selectButton2List.removeOne(button);
    delete button;
}


bool MainWindow::canUpdate1()
{
    if(m_playerGold>=300)//后续可做调整
    {
        return true;
    }
    return false;
}

bool MainWindow::canUpdate2()
{
    if(m_playerGold>=400)//后续视游戏效果做调整
    {
        return true;
    }
    return false;
}

QList<Enemy *>& MainWindow::getEnemyList()
{
    return m_enemyList;
}

void MainWindow::removeBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);
    m_bulletList.removeOne(bullet);
    delete bullet;
}

void MainWindow::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);
    m_bulletList.push_back(bullet);
}

void MainWindow::awardGold(int i)//每次杀死敌人后的金币奖励
//要根据敌人类型进行区分啊（所以enemy类必须有一个参数是类型）
{
    m_playerGold+=200;
    update();
}

void MainWindow::getHpDamage()
{
    m_playerHp-=1;
    if(m_playerHp<=0)
    {
        doGameOver();
    }
}

void MainWindow::doGameOver()
{
    if(!m_gameLose)
    {
        m_gameLose=true;
    }
}

//绘画函数
void MainWindow::drawWaves(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::red);//这里具体的参数确定了位置
    painter->drawText(QRect(500,5,100,25),QString("WAVES: %1").arg(m_waves+1));
    painter->drawPixmap(450,5,25,25,wave_sprite);
    painter->restore();
}

void MainWindow::drawHp(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(50,5,100,25),QString("HP: %1").arg(m_playerHp));
    painter->drawPixmap(10,5,25,25,Hp_sprite);
    painter->restore();
}

void MainWindow::drawGold(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(300,5,100,25),QString("GOLD: %1").arg(m_playerGold));
    painter->drawPixmap(10,5,25,25,Hp_sprite);
    painter->restore();//为何这个之前并没有写
}

bool MainWindow::loadWaves()
{
    if(m_waves>=6)
    {
        return false;
    }

    int enemyStartInterval1[]={100,500,600,1000,3000,6000};
    int enemyStartInterval2[]={100,800,2000,4000,10000,20000};
    int enemyStartInterval3[]={100,300,500,700,1000,1500};//敌人出现的越密集越不好打，但是观感就不是很好了
    for(int i=0;i<6;++i)
    {
        wayPoint * startWayPoint;
        startWayPoint=m_wayPointList.first();

        Enemy * enemy=new Enemy(startWayPoint,this,i);
        //Boss* enemy=new Boss(startWayPoint,this);
        m_enemyList.push_back(enemy);

        enemy->reSetHp(40+60*(0+m_waves));//波数增加，怪物的血量增加，一次加20点
        enemy->reSetSpeed(m_waves/2+1);

        if(m_waves==0||m_waves==3) QTimer::singleShot(enemyStartInterval1[i],enemy,SLOT(doActive()));
        else if(m_waves==1||m_waves==4) QTimer::singleShot(enemyStartInterval2[i],enemy,SLOT(doActive()));//纠正了等于号写成赋值号的问题
        else if(m_waves==2||m_waves==5) QTimer::singleShot(enemyStartInterval3[i],enemy,SLOT(doActive()));
    }
    return true;
}

void MainWindow::build_tower(int i,QList<TowerPosition>::iterator it)//i代表塔的类型 //这里iterator的i是小写
{
    QPixmap path[5]={};
    if(canBuyTower(i))
    {
        it->sethasTowers(i,true);
        m_playerGold-=tower1Cost;
        Defend_Tower * tower=new Defend_Tower(it->getCenterPos(),this,i);//四个参数，分别是防御塔的中心点；主界面；防御塔类型。
        it->setTower(tower);
        m_towerList.push_back(tower);
        update();
    }
}

void MainWindow::mousePressEvent(QMouseEvent * event)
{
    QPoint pressPos=event->pos();
    auto it=m_towerPositionList.begin();
    while(it!=m_towerPositionList.end())
    {
        if(Qt::LeftButton==event->button())//如果是鼠标左键点击
        {//左键点击的情况下，可以实现防御塔选择button的出现和防御塔的选择,或者是在有button2的情况下，进行升级或移除的操作
            if(it->ContainPos(pressPos) && !it->hasButton() && !it->hasTower() && !it->hasButton2())//在没有按钮的情况下点击，会出现button1
            {
                QPoint tmp(it->getPos().x()-35,it->getPos().y()-35);//向左上角移动35 35，得到选择框的端点
                selectButton * button=new selectButton(tmp,this);//构造一个选择框
                m_selectButtonList.push_back(button);//类似防御塔的放置，把这个button放到MainWindow的一个list中
                it->setButton(button);//设置这个防御塔坑处的button
                it->setHasButton(true);//这个坑有了button
                update();//更新mainwindow，主要是更新paintevent
                break;
            }
            //下面的判断语句，要先判断hasbutton2，不能先判断containPos.因为如果没有button2，在进入这个判断框的时候，会先getbutton2，但是button2是NULL，程序会异常结束。
            else if(it->hasButton2() && it->getButton2()->containPos(pressPos) && !it->hasButton() && !it->ContainPos(pressPos) &&it->hasTower())
            {//在有button2的情况下，点击button2的内部
                if(pressPos.y()<(it->getButton2()->getPos().y()+25))//我直接设置了第一个选择框的height是25，这里就直接用25了
                //通过y坐标来实现判断到底是摁remove还是upgrade
                {//对防御塔进行升级
                    if(canUpdate1() && !it->hasUpdate1() && it->hasTower())
                    {
                        it->sethasUpdate1(true);
                        m_playerGold-=towerupdate1Cost;
                        it->get_tower()->reSetDamage(it->get_tower()->getDamage()+50);//不仅是攻击力要提升，图片也可以改变
                        it->get_tower()->levelChange();
                    }
                    else if(canUpdate2() && it->hasUpdate1() && !it->hasUpdate2())
                    {
                        it->sethasUpdate2(true);
                        m_playerGold-=towerupdate2Cost;
                        it->get_tower()->reSetDamage(it->get_tower()->getDamage()+100);
                        it->get_tower()->levelChange();
                    }
                }
                else if(pressPos.y()>it->getButton2()->getPos().y()+25)
                {//对防御塔进行移除
                    awardGold();//移除防御塔奖励200
                    it->get_tower()->getRemoved();//这个移除和前面写的几个移除都是一样的
                    it->setRemoveTower();
                }
                //点击了button2的内部，button2就要被移除 //但是点击外部也应该消除button1 和 button2
                it->getButton2()->getRemoved();
                it->setButton2(NULL);
                it->setHasButton2(false);
                update();
                break;
            }
            else if(it->hasButton() && !it->hasTower() && it->getButton()->containPos(pressPos))//在有button的情况下，选择三种炮台.其实这里代码有点重复了。如果用继承的方法，那就应该不要这么多的重复代码
            {
                if(pressPos.x()<it->getButton()->getPos().x()+35)//鼠标点在选择框中的第一个防御塔内
                {
                    build_tower(1,it);
                }
                else if(pressPos.x()>it->getButton()->getPos().x()+35 && pressPos.x()<it->getButton()->getPos().x()+70)//鼠标点在第二个防御塔的图片中
                {
                    build_tower(2,it);
                }
                else if(pressPos.x()>it->getButton()->getPos().x()+70 && pressPos.x()<it->getButton()->getPos().x()+105)//第三个图片
                {
                    build_tower(3,it);
                }
                else if(pressPos.x()>it->getButton()->getPos().x()+105 && pressPos.x()<it->getButton()->getPos().x()+140) //第四个图片
                {
                    build_tower(4,it);
                }
                //不能跳出循环是因为要执行下面的代码
                //下面的代码是对button的一个删除
                it->getButton()->getRemoved();
                it->setButton(NULL);
                it->setHasButton(false);
                update();
                break;
            }
        }
        else if(Qt::RightButton==event->button())//如果是鼠标右键点击
        {//在有防御塔的情况下，右键会出现选择框，升级还有移除
            if(it->ContainPos(pressPos) && (!it->hasButton2()) && it->hasTower())
            {
                it->setHasButton2(true);
                QPoint tmp(it->getPos().x()+35,it->getPos().y());//我是把防御塔坑的右上顶点当作button2的端点
                selectButton2* button2=new selectButton2(tmp,this);//这里之前有一个小笔误
                button2->setTower(it->get_tower());//我写这个setTower()的目的是得到防御塔的等级，不同等级的updatecost不一样，具体的你可以看button2的draw方法
                m_selectButton2List.push_back(button2);
                it->setButton2(button2);
                update();
                break;
            }
        }
        ++it;
    }
}
