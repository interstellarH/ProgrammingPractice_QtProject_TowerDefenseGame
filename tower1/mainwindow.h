#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>

#include "waypoint.h"
#include "towerposition.h"
#include "enemy.h"
#include "bullet.h"
#include "auxiliary_function.h"
#include "defend_tower.h"
#include "selectbutton.h"
#include "selectbutton2.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class wayPoint;//新增对wayPoint类的说明

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int lev,QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent*);
    QString getpath();
    void setpath(QString path);
    void addWayPoint1();
    void addWayPoint2();
    void addWayPoint3();//用来添加航点的函数,分别为三个关卡绘制航点

    void loadTowerPosition1();
    void loadTowerPosition2();
    void loadTowerPosition3();//加载防御塔坑位


    void getHp();//获取玩家当前血量的函数
    void getHpHurted();//敌人抵达终点，玩家扣血
    void removeEnemy(Enemy *enemy);//敌人死亡之后触发

    QList<Enemy *>getEnemyList;//获取Enemy_list

    bool loadWaves();

    void removeBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);

    bool canButTower(int i);//判断是否可以买第i种塔
    void removeButton(selectButton * button);//在mainwindow中对button进行移除

    void removeButton2(selectButton2 * button);//在mainwindow中对button2进行移除
    void removeTower(Tower * tower);

    bool canUpdate1();//判断是否可以第一次升级
    bool canUpdate2();//判断是否可以第二次升级

private:
    Ui::MainWindow *ui;
    QString nowpath;
    int level;//关卡数
    QList<wayPoint * > m_wayPointList;
    QList<wayPoint * > m_wayPointList1;
    QList<wayPoint * > m_wayPointList2;//第三关有三条路径
    QList<TowerPosition> m_towerPositionList;

    QList<Enemy *> m_enemyList;//用来储存敌人的list
    QList<Bullet *>m_bulletList;//用来存储子弹的list
    QList<selectButton * > m_selectButtonList;//用来储存selectButton的list
    QList<selectButton2 *> m_selectButton2List;//用来储存selectButton2的list

    int m_playerHp;//基地的血量
    int m_playerGlod;//初始金币
    int m_waves;//关卡的波数
    bool m_gameWin;
    bool m_gameLose;

    void mousePressEvent(QMouseEvent *);

private slots:
    void updateMap();
    void gameStart();
};
#endif // MAINWINDOW_H
