#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>

#include "waypoint.h"//我们一般引用系统内文件时，用<>,引用我们自己定义的文件时用""

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class wayPoint;//新增对wayPoint类的说明

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addWayPoint1();//用来添加航点的函数
private:
    Ui::MainWindow *ui;
    QList<wayPoint * > m_wayPointList;

protected:
    void paintEvent(QPaintEvent*);
};

#endif // MAINWINDOW_H
