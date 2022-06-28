#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QString>
#include <QPainter>
#include <QSize>

#include "waypoint.h"

class MainWindow;
class Tower;
class QPainter;
class wayPoint;

class Enemy:public QObject
{
    Q_OBJECT
public:
    Enemy(wayPoint * startPoint, MainWindow * game,const QPixmap & pic);
    ~Enemy();
    void draw(QPainter * painter)const;
    void move();//敌人的移动

    QPoint getPos();//得到敌人的当前位置

    void getAttacked(Tower * tower);//被tower攻击
    void getDamaged(int damage);//敌人被攻击受到伤害
    void getRemoved();//当血量非正时，敌人死亡，需要移除
    void getLostSight(Tower * tower);//敌人脱离tower的攻击范围

    void getFrozen();//被防御塔定住
    void removeFrozen();//解除被定住负面状态
    
    int getPhysicalRe();//获得物理抗击值
    int getMagicalRe();//获得魔法抗击值

    void reSetHp(int maxHp);
    void reSetSpeed(int times);

private slots:
    void doActive();//私有信号槽，敌人是否可以移动

private:
    int e_maxHp;//最大血量
    int e_currentHp;//当前血量
    int e_physicalRe;//物理抗击
    int e_magicalRe;//魔法抗击
    int e_speed;//移动速度
    bool e_active;//是否可以移动

    wayPoint * e_destinationWayPoint;//目标航点的指针
    MainWindow * e_game;//mainwindow的指针
    QPoint e_pos;//当前位置
    QString e_path;//图片路径
    QPixmap e_pic;//
    QList<Tower *> e_attackerTowerList;//正在攻击该敌人的防御塔list

    static const QSize e_fixedSize;
};

#endif // ENEMY_H

