#ifndef DEFEND_TOWER_H
#define DEFEND_TOWER_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QString>
#include <QTimer>

#include "enemy.h"

class MainWindow;
class QPainter;
class Enemy;

class Defend_Tower:QObject{
    Q_OBJECT
public:
    Defend_Tower(QPoint pos,MainWindow *game,QString path);//文件路径记得更改
    ~Defend_Tower();
    Defend_Tower();

    void draw(QPainter *painter)const;

    void physical_AttackEnemy();
    void magical_AttackEnemy();
    void targetKilled();
    void chooseEnemyFromAttack(QList<Enemy *> enemy);//从可以攻击的敌人中，选出攻击的敌人
    void checkEnemyInRange();//检查敌人是否在攻击范围内
    //单体攻击、群体攻击
    void removeBullet();//移除防御塔产生的子弹
    void lostSightOfEnemy();//丢失攻击目标的视野
    Enemy * getAttackedEnemy();//得到正在攻击的敌人
    //范围攻击
    void pauseEnemy();

    //升级与拆除
    void reSetDamage(int damage);//重新设置攻击力
    int getDamgae();//得到防御塔的攻击力
    void levelChange();//防御塔升级
    int getLevel();//得到防御塔的等级

    void getRemoved();//防御塔被移除

private:
    QPoint t_pos;//防御塔中心点
    QString t_path;//防御塔图片路径

    int t_attackrange;//攻击范围
    static const QSize t_picturesize;//防御塔图片大小
    MainWindow * t_game;


    bool t_attacking;//是否在攻击
    int t_damage;//防御塔的攻击力
    int t_magical;//防御塔的破魔属性值
    int t_attackGroupRange;//群体攻击炮塔的爆炸范围or范围塔的定时范围 单体炮塔此项为0
    int t_fireRate;//射速or攻击间隔
    QList<Enemy *> t_attackerList;//正在攻击的敌人的list（单体攻击时size为1，群体攻击时目标中心点在front位置，其余在后面）
    QTimer * t_fireRateTime;//开始攻击的计时器

private slots:
    void shootWeapon();//实现和子弹类的连接
};
#endif // DEFEND_TOWER_H
