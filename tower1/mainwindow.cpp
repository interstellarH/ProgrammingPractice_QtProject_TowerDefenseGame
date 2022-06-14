#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QSize>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(QSize(800,500));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);


    painter.drawPixmap(0,0,this->width(),this->height(),nowpath);
}

QString MainWindow::getpath()
{
    return nowpath;
}

void MainWindow::setpath(QString path)
{
    nowpath=path;
}
