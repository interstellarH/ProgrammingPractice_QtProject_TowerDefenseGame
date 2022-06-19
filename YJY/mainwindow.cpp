#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QSize>
#include <QList>
#include "towerposition.h"
#include "waypoint.h"
#include "selectbutton.h"
#include "selectbutton2.h"

MainWindow::MainWindow(int lev,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),level(lev)
{
    ui->setupUi(this);
    this->resize(QSize(800,500));
    if(level==1)loadTowerPosition1();
    else if(level==2)loadTowerPosition2();
    else if(level==3)loadTowerPosition3();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);


    painter.drawPixmap(0,0,this->width(),this->height(),nowpath);
    if(level==1||level==2)
    {
        foreach(const wayPoint * waypoint, m_wayPointList)
           waypoint->draw(&painter);
    }
    else if(level==3)
    {
        foreach(const wayPoint * waypoint, m_wayPointList)
           waypoint->draw(&painter);
        foreach(const wayPoint * waypoint, m_wayPointList1)
           waypoint->draw(&painter);
        foreach(const wayPoint * waypoint, m_wayPointList2)
           waypoint->draw(&painter);
    }


    foreach(const TowerPosition towerposition,m_towerPositionList)
        towerposition.draw(&painter);
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
    if(m_playerGlod>=400)
    {
        return true;
    }
    return false;
}

void MainWindow::removeButton(selectButton *button)
{
    m_selectButtonList.removeOne(button);
}

void MainWindow::removeTower(Defend_Tower *tower)
{
    m_towerList.removeOne(tower);
}

void MainWindow::removeButton2(selectButton2 *button)
{
    m_selectButton2List.removeOne(button);
}

bool MainWindow::canUpdate1()
{
    if(m_playerGlod>=300)//后续可做调整
    {
        return true;
    }
    return false;
}

bool MainWindow::canUpdate2()
{
    if(m_playerGlod>=400)//后续视游戏效果做调整
    {
        return true;
    }
    return false;
}
