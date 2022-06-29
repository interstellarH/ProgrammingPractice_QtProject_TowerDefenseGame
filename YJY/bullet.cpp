#include "bullet.h"
#include "defend_tower.h"
#include "mainwindow.h"
#include "auxiliary_function.h"
#include "enemy.h"
#include <QPoint>
#include <QPainter>
#include <QString>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

Bullet::Bullet(QPoint startPos,QPoint targetPos,Defend_Tower* tower,MainWindow * game,int damage,int magical):
    b_startPos(startPos),b_targetPos(targetPos),b_tower(tower),b_game(game),b_damage(damage),b_magical(magical)
{
    b_targetEnemy=tower->getAttackedEnemy();
    b_sprite=QPixmap(":/new/prefix1/resource1/bullet.png");
}

QPoint Bullet::getCurrentPos()
{
    return b_currentPos;
}

void Bullet::setCurrentPos(QPoint pos)
{
    b_currentPos = pos;
}

void Bullet::move()
{
    int duration=100;//子弹飞行的时间，经过100ms击中敌人
    QPropertyAnimation * animation=new QPropertyAnimation(this,"b_currentPos");
    animation->setDuration(duration);//设置持续时间
    animation->setStartValue(b_startPos);//设置起始位置
    animation->setEndValue(b_targetPos);//设置目标位置
    connect(animation,SIGNAL(finished()),this,SLOT(hitTarget()));//连接信号槽，击中敌人后，子弹动态运动结束
    animation->start();
}

void Bullet::hitTarget()
{
    QList<Enemy*> enemylist;
    enemylist.append(b_tower->getAttackedEnemy());
    foreach(Enemy* attack_enemy, b_game->getEnemyList()){
        if(attack_enemy==b_tower->getAttackedEnemy())continue;
        if(collisionWithCircle(attack_enemy->getPos(),b_tower->get_attackGroupRange(),b_targetPos,0)){
            enemylist.append(attack_enemy);
        }
    }
    while(!enemylist.empty()){//设置物理攻击和魔法攻击的区别
        int harm;
        harm = b_damage-b_magical*enemylist.front()->getMagicalRe();//计算公式：攻击值-魔攻值*攻击对象魔抗
        enemylist.front()->getDamaged(harm);
        enemylist.pop_front();
    }
    b_game->removeBullet(this);//击中敌人后子弹就要消失
}

void Bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(b_currentPos,b_sprite);
}


Physical_Bullet::Physical_Bullet(QPoint startPos,QPoint targetPos,Defend_Tower* tower,
                                 MainWindow * game):
    Bullet(startPos, targetPos, tower, game, tower->getDamage(),0)
{
}


Magical_Bullet::Magical_Bullet(QPoint startPos,QPoint targetPos,Defend_Tower* tower,
                               MainWindow * game):
                               Bullet(startPos, targetPos, tower, game,
                                      tower->getDamage(), tower->getMagical())
{
}


void Physical_Explosion::hitTarget()
{
    QList<Enemy*> enemylist;
    enemylist.append(b_targetEnemy);
    foreach(Enemy* attack_enemy, b_game->getEnemyList()){
        if(attack_enemy==b_tower->getAttackedEnemy())continue;
        if(collisionWithCircle(attack_enemy->getPos(),b_range,b_targetPos,0)){
            enemylist.append(attack_enemy);
        }
    }
    while(!enemylist.empty()){//设置物理攻击和魔法攻击的区别
        int harm;
        harm = b_damage-b_magical*enemylist.front()->getMagicalRe();//计算公式：攻击值-魔攻值*攻击对象魔抗
        enemylist.front()->getDamaged(harm);
        enemylist.pop_front();
    }
    b_game->removeBullet(this);//击中敌人后子弹就要消失
}

int Physical_Explosion::getOpacity()const{
    return cur_Opacity;
}

void Physical_Explosion::setOpacity(int x){
    cur_Opacity = x;
}

void Physical_Explosion::OpacityChanged(){
    b_game->removePoint(this,1);//将最终运动的位置移除list1
}

void Physical_Explosion::drawExplosion(QPainter *painter)const{
    painter->setOpacity(cur_Opacity);
    painter->drawPixmap(b_targetPos,b_explodePath);
}


Frozen_Bullet::Frozen_Bullet(QPoint startpos,Defend_Tower* tower,MainWindow * game,int time):
    Bullet(startpos,QPoint(NULL,NULL),tower,game)
{
    b_FrozenTime = time;
    b_range = tower->get_attackGroupRange();
    b_sprite=QPixmap(":/new/prefix/resource1/Iceball.png");
}

void Frozen_Bullet::move(){
    enemylist.push_back(b_targetEnemy);
    foreach(Enemy* attack_enemy, b_game->getEnemyList()){
        if(attack_enemy==b_tower->getAttackedEnemy())continue;
        if(collisionWithCircle(attack_enemy->getPos(),b_tower->get_attackGroupRange(),b_targetPos,0)){
            enemylist.append(attack_enemy);
        }
    }
    int duration=100;//子弹飞行的时间，经过100ms击中敌人
    QPropertyAnimation * animation=new QPropertyAnimation(this,"b_currentPos");
    animation->setDuration(duration);//设置持续时间
    animation->setStartValue(b_startPos);//设置起始位置
    animation->setEndValue(b_targetPos);//设置目标位置
    connect(animation,SIGNAL(finished()),this,SLOT(hitTarget()));//连接信号槽，击中敌人后，子弹动态运动结束
    animation->start();
}

void Frozen_Bullet::hitTarget(){
    foreach(Enemy * attack_enemy, enemylist){
        attack_enemy->getFrozen();
    }
    QPropertyAnimation * animation=new QPropertyAnimation(this,"b_CurTime");
    animation->setDuration(b_FrozenTime);//设置持续时间
    animation->setStartValue(0);//设置起始时间
    animation->setEndValue(b_FrozenTime);//设置终止时间
    connect(animation,SIGNAL(finished()),this,SLOT(reset_speed()));//连接信号槽，时间结束后动画结束
    animation->start();
    b_game->removeBullet(this);
}

void Frozen_Bullet::reset_speed(){
    foreach(Enemy * attack_enemy, enemylist){
        attack_enemy->removeFrozen();
    }
}
int Frozen_Bullet::getCurTime()const
{
    return b_CurTime;
}

void Frozen_Bullet::setTime(int x){
    b_CurTime=x;
}
