#include "start.h"
#include "./ui_start.h"
#include "mainwindow.h"
#include <QWindow>
#include <QPainter>
#include <QSize>
#include <QString>


start::start(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::start)
{
    ui->setupUi(this);
    this->resize(QSize(500,500));
    ui->label->setText("家瑛今天吃什么");
}

start::~start()
{
    delete ui;
}

void start::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QString path(":/new/prefix1/resource1/background.jpg");

    painter.drawPixmap(0,0,this->width(),this->height(),path);
}

void start::on_pushButton_clicked()
{
    MainWindow* first=new MainWindow(1);
    first->setpath(":/new/prefix1/resource1/background1.jpg");
    first->setWindowTitle("第一关 程设期中考试");
    first->show();
    first->addWayPoint1();
}


void start::on_pushButton_2_clicked()
{
    MainWindow* second=new MainWindow(2);
    second->setpath(":/new/prefix1/resource1/background2.jpg");
    second->setWindowTitle("第二关 魔兽世界大作业");
    second->show();
    second->addWayPoint2();
}


void start::on_pushButton_3_clicked()
{
    MainWindow* third=new MainWindow(3);
    third->setpath(":/new/prefix1/resource1/background3.jpg");
    third->setWindowTitle("第三关 QT大作业");
    third->show();
    third->addWayPoint3();
}

