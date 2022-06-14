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
    QString path(":/new/prefix1/resource1/20220527222135.jpg");

    painter.drawPixmap(0,0,this->width(),this->height(),path);
}

void start::on_pushButton_clicked()
{
    MainWindow* first=new MainWindow();
    first->setpath(":/new/prefix1/resource1/20220527194540.jpg");
    first->setWindowTitle("第一关 程设期中考试");
    first->show();
}


void start::on_pushButton_2_clicked()
{
    MainWindow* second=new MainWindow();
    second->setpath(":/new/prefix1/resource1/20220527194453.jpg");
    second->setWindowTitle("第二关 魔兽世界大作业");
    second->show();
}


void start::on_pushButton_3_clicked()
{
    MainWindow* third=new MainWindow();
    third->setpath(":/new/prefix1/resource1/20220527194528.jpg");
    third->setWindowTitle("第三关 QT大作业");
    third->show();
}

