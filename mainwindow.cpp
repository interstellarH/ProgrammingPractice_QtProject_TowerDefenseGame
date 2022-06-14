#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waypoint.h"

#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QPushButton>
#include <QDebug>
#include <QPoint>
#include <QTimer>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addWayPoint1();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QString path("E:/Qt/Tower/images/background1.jpg");//path是你图片的路径

    painter.drawPixmap(0,0,750,375,path);
    //drawPixmap的前四个参数代表的分别是，图片左上角的横坐标，图片左上角的纵坐标，图片的width，图片的height。我们一般把width和height，与图片的真实大小匹配起来
    foreach(const wayPoint * waypoint, m_wayPointList)
        waypoint->draw(&painter);
}
void MainWindow::addWayPoint1()
{
    wayPoint * waypoint1=new wayPoint(QPoint(79,6));
    m_wayPointList.push_back(waypoint1);

    wayPoint * waypoint2=new wayPoint(QPoint(79,55));
    waypoint1->setNextWayPoint(waypoint2);
    m_wayPointList.push_back(waypoint2);

    wayPoint * waypoint3=new wayPoint(QPoint(407,55));
    waypoint2->setNextWayPoint(waypoint3);
    m_wayPointList.push_back(waypoint3);

    wayPoint * waypoint4=new wayPoint(QPoint(407,175));
    waypoint3->setNextWayPoint(waypoint4);
    m_wayPointList.push_back(waypoint4);

    wayPoint * waypoint5=new wayPoint(QPoint(83,175));
    waypoint4->setNextWayPoint(waypoint5);
    m_wayPointList.push_back(waypoint5);

    wayPoint * waypoint6=new wayPoint(QPoint(83,292));
    waypoint5->setNextWayPoint(waypoint6);
    m_wayPointList.push_back(waypoint6);

    wayPoint * waypoint7=new wayPoint(QPoint(473,292));
    waypoint6->setNextWayPoint(waypoint7);
    m_wayPointList.push_back(waypoint7);
}

